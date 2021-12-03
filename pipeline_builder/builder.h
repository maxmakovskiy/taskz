#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <exception>
#include <utility>
#include <functional>

struct Email 
{
    std::string from;
    std::string to;
    std::string body;
};


class Worker 
{
public:
    virtual ~Worker() = default;
    virtual void Process(std::unique_ptr<Email> email) = 0;
    virtual void Run() {
        throw std::logic_error("Unimplemented");
    }

protected:
    void PassOn(std::unique_ptr<Email> email) const
    {
        if (nextWorker) {
            nextWorker->Process(std::move(email));
        }
    }

public:
    void SetNext(std::unique_ptr<Worker> next)
    {
        nextWorker = std::move(next);
    }

private:
    std::unique_ptr<Worker> nextWorker;

};


class Reader : public Worker 
{
public:
    Reader(std::istream& is)
        : source(is)
    {
    }

    void Process(std::unique_ptr<Email> email) override
    {
        PassOn(std::move(email)); 
    }

    void Run() override
    {
        bool notEofStatus = true;
        while (notEofStatus)
        {
            auto [email, status] = ReadEmailFromStream();
            if (status) {
                Process(std::make_unique<Email>(std::move(email)));                    
            }

            notEofStatus = status;
        }
    }

private:
    std::istream& source;

    std::pair<Email, bool> ReadEmailFromStream() 
    {
        std::string from, to, body;
        bool success = std::getline(source, from)
            && std::getline(source, to)
            && std::getline(source, body);

        Email email = {from, to, body};
        return std::make_pair(email, success);
    }

};


class Filter : public Worker 
{
public:
    using Function = std::function<bool(const Email&)>;

    Filter(Function pred)
        : predicate(pred)
    {
    }


    void Process(std::unique_ptr<Email> email) override
    {
        if (predicate(*email)) {
            PassOn(std::move(email));
        }
    }

private:
    Function predicate;

};


class Copier : public Worker 
{
public:
    Copier(const std::string& recipient) 
        : target(recipient) 
    {
    }

    void Process(std::unique_ptr<Email> email) override
    {
        if (email->to == target)
        {
            PassOn(std::move(email));
            return;
        }
        
        Email copyMail = {email->from, target, email->body};
        PassOn(std::move(email));
        PassOn(std::make_unique<Email>(copyMail));
    }

private:
    std::string target;
};


class Sender : public Worker 
{
public:
    Sender(std::ostream& output)
        : os(output) 
    {
    }
    
    void Process(std::unique_ptr<Email> email) override
    {
        os << email->from << '\n' 
           << email->to << '\n' 
           << email->body << '\n';

        PassOn(std::move(email));
    }

private:
    std::ostream& os;

};


class PipelineBuilder 
{
public:
    explicit PipelineBuilder(std::istream& in)
    {
        workers.push_back(std::make_unique<Reader>(in));
    }

    PipelineBuilder& FilterBy(Filter::Function filter)
    {
        workers.push_back(std::make_unique<Filter>(filter));
        return *this;
    }

    PipelineBuilder& CopyTo(std::string recipient)
    {
        workers.push_back(std::make_unique<Copier>(recipient));
        return *this;
    }

    PipelineBuilder& Send(std::ostream& out)
    {
        workers.push_back(std::make_unique<Sender>(out));
        return *this;
    }

    std::unique_ptr<Worker> Build()
    {
        // propage through all workers SetNext 
        for (int i = workers.size() - 2; i >= 0; --i)
        {
            workers[i]->SetNext(std::move(workers[i+1]));
        }
        
        return std::move(workers.front());
    }

private:
    std::vector<std::unique_ptr<Worker>> workers;

};


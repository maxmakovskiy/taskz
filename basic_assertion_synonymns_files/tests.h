#pragma once

#include "test_runner.h"
#include "synonymns.h"

void TestAddNewPair()
{
    SynonymnsManager manager;
    manager.AddNewPair("word1", "word2");
    manager.AddNewPair("word1", "word3");
    manager.AddNewPair("word2", "word3");
    manager.AddNewPair("word2", "word4");
        
    const Synonymns expected = { 
        {"word1", {"word2", "word3"}},
        {"word2", {"word1", "word3", "word4"}},
        {"word3", {"word1", "word2"}},
        {"word4", {"word2"}}
    };
        
    AssertEqual(manager.GetAll(), expected, "Add new pairs to empty dictionary");
}

void TestSynonymnCountByWord()
{
    SynonymnsManager manager;
    manager.AddNewPair("word1", "word2");
    manager.AddNewPair("word1", "word3");
    manager.AddNewPair("word2", "word3");
    manager.AddNewPair("word2", "word4");
   
    AssertEqual(manager.SynonymnCountByWord("word1"), 2u, "SynonymnCountByWord(word1)");
    AssertEqual(manager.SynonymnCountByWord("word2"), 3u, "SynonymnCountByWord(word2)");
    AssertEqual(manager.SynonymnCountByWord("word3"), 2u, "SynonymnCountByWord(word3)");
    AssertEqual(manager.SynonymnCountByWord("word4"), 1u, "SynonymnCountByWord(word4)");
    AssertEqual(manager.SynonymnCountByWord("word5"), 0u, "SynonymnCountByWord(word5)");
}

void TestAreSynonymns()
{
    SynonymnsManager manager;
    manager.AddNewPair("word1", "word2");
    manager.AddNewPair("word1", "word3");
    manager.AddNewPair("word2", "word3");
    manager.AddNewPair("word2", "word4");
   
    Assert(manager.AreSynonymns("word1", "word2"), "word1 is synonymn for word2");
    Assert(manager.AreSynonymns("word2", "word3"), "word2 is synonymn for word3");
    Assert(manager.AreSynonymns("word2", "word4"), "word2 is synonymn for word4");
    Assert(!manager.AreSynonymns("word3", "word4"), "word2 is not synonymn for word4");

}

void AllTests()
{
    TestRunner runner;
    runner.RunTest(TestAddNewPair, "TestAddNewPair");
    runner.RunTest(TestSynonymnCountByWord, "TestSynonymnCountByWord");
    runner.RunTest(TestAreSynonymns, "TestAreSynonymns");
}
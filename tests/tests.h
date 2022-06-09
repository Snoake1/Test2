#ifndef EQTEST_H
#define EQTEST_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <string>
#include <fstream>

extern "C"{
#include "text/text.h"
#include "text/_text.h"
#include "common.h"
}

char* filename = "input.txt";
char* oneline = "oneline.txt";

TEST(load, correct_load)
{
    text txt = create_text();
    EXPECT_EQ(txt->begin, nullptr);
    EXPECT_EQ(txt->end, nullptr);
    load(txt, filename);
    std::ifstream f;
    std::string s;
    EXPECT_NE(txt->begin, nullptr);
    EXPECT_NE(txt->end, nullptr);
    node *current = txt->begin;
    while(std::getline(f, s))
    {
    EXPECT_EQ(current->contents, s);
	current=current->next;
    }
}

TEST(save, saved){
    text txt = create_text();
    load(txt, filename);
    save(txt, "output.txt");
    std::ifstream f;
    f.open(filename);
    std::ifstream c;
    c.open("output.txt");
    std::string s;
    std::string s_c;
    while(std::getline(f, s) && std::getline(c, s_c)){
        EXPECT_EQ(s, s_c);
    }
    f.close();
    c.close();
    remove_all(txt);
}

TEST(move_cursor, normal)
{
    text txt = create_text();
    load(txt, filename);
    mcursor(txt, 2, 3);
    EXPECT_EQ(txt->cursor->position, 3);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
	k++;
	current = current->next;
    }
    EXPECT_EQ(k, 2);
    remove_all(txt);
}

TEST(move_cursor, normalpar)
{
    text txt = create_text();
    load(txt, filename);
    mcursor(txt, 2, 4);
    EXPECT_EQ(txt->cursor->position, 4);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
	k++;
	current = current->next;
    }
    EXPECT_EQ(k, 2);
    remove_all(txt);
}
TEST(move_cursor, minusvaluestr)
{
    text txt = create_text();
    load(txt, filename);
    mcursor(txt, -9, 0);
    EXPECT_EQ(txt->cursor->position, 0);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
	k++;
	current = current->next;
    }
    EXPECT_EQ(k, 1);
    remove_all(txt);
}

TEST(move_cursor, mvzero)
{
    text txt = create_text();
    load(txt, filename);
    mcursor(txt, 15, 0);
    EXPECT_EQ(txt->cursor->position, 0);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
	k++;
	current = current->next;
    }
    EXPECT_EQ(k, txt->length);
    remove_all(txt);
}

TEST(move_cursor, minusvalue)
{
    text txt = create_text();
    load(txt, filename);
    mcursor(txt, 2, -10);
    EXPECT_EQ(txt->cursor->position, 0);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
	k++;
	current = current->next;
    }
    EXPECT_EQ(k, 2);
    remove_all(txt);
}

TEST(move_cursor, endofstr)
{
    text txt = create_text();
    load(txt, filename);
    mcursor(txt, 2, 40);
    EXPECT_EQ(txt->cursor->position, 40);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
	k++;
	current = current->next;
    }
    EXPECT_EQ(k, 2);
    remove_all(txt);
}

TEST(rmstr, firststr)
{
    text txt = create_text();
    load(txt, filename);
    unsigned long ln1 = txt->length;
    mcursor(txt, 0, 0);
    rc(txt);
    unsigned long ln2 = txt->length;
    EXPECT_EQ(ln1 - 1, ln2);
    remove_all(txt);
}
TEST(rmstr, nstr)
{
    text txt = create_text();
    load(txt, filename);
    mcursor(txt, 1, 1);
    char* firstline = txt->cursor->line->contents;
    unsigned long ln1 = txt->length;
    mcursor(txt, 3, 1);
    ln1--;
    rc(txt);
    unsigned long ln2 = txt->length;
    EXPECT_EQ(txt->cursor->position, 0);
    EXPECT_EQ(ln1, ln2);
    EXPECT_EQ(firstline, txt->begin->contents);
    remove_all(txt);
}

TEST(rmstr, onestr)
{
  text txt = create_text();
  load(txt, oneline);
  rc(txt);
  EXPECT_EQ(txt->begin, nullptr);
  remove_all(txt);
}

TEST(rmstr, laststr)
{
    text txt = create_text();
    load(txt, filename);
    unsigned long ln1 = txt->length;
    mcursor(txt, 1000000, 1);
    rc(txt);
    unsigned long ln2 = txt->length;
    EXPECT_EQ(txt->cursor->position, 0);
    EXPECT_EQ(ln1 - 1, ln2);
    remove_all(txt);
}

TEST(mwbb, normal)
{
    text txt = create_text();
    load(txt, filename);
    mcursor(txt, 2, 3);
    txt = mwbb(txt);
    EXPECT_EQ(txt->cursor->position, 0);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
    k++;
    current = current->next;
    }
    EXPECT_EQ(k, 2);
    remove_all(txt);
}

TEST(mwbb, twospace)
{
    text txt = create_text();
    load(txt, oneline);
    mcursor(txt, 1, 16);
    mwbb(txt);
    EXPECT_EQ(txt->cursor->position, 16);
    remove_all(txt);
}

TEST(mwbb, space)
{
    text txt = create_text();
    load(txt, filename);
    mcursor(txt, 2, 10);
    txt = mwbb(txt);
    EXPECT_EQ(txt->cursor->position, 10);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
    k++;
    current = current->next;
    }
    EXPECT_EQ(k, 2);
    remove_all(txt);
}

TEST(mwbb, lword)
{
    text txt = create_text();
    load(txt, filename);
    mcursor(txt, 2, 8);
    txt = mwbb(txt);
    EXPECT_EQ(txt->cursor->position, 0);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
    k++;
    current = current->next;
    }
    EXPECT_EQ(k, 2);
    remove_all(txt);
}

#endif

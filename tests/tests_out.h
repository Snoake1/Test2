#ifndef TEST_OUT_H
#define TEST_OUT_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <string>
#include <fstream>
#include <string>

extern "C"{
#include "text/text.h"
#include "text/_text.h"
#include "common.h"
}

char* filenm = "input.txt";

TEST(load, noreadfile)
{
    text txt = create_text();
    testing::internal::CaptureStdout();
    load(txt, "notrealfile.txt");
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, "The file notrealfile.txt cannot be opened\n");
    remove_all(txt);
}
/*
TEST(save, nowritefile)
{
    text txt = create_text();
    load(txt, filenm);
    testing::internal::CaptureStdout;
    save(txt, "nowritefile.txt");
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, "The file nowritefile.txt cannot be written\n");
    remove_all(txt);
} */

TEST(save, nofile)
{
    text txt = create_text();
    testing::internal::CaptureStderr;
    save(txt, "out.txt");
    std::string outp = testing::internal::GetCapturedStderr();
    EXPECT_EQ(outp, "The text doesn`t exist\n");
    remove_all(txt);
}

TEST(move_cursor, outerr)
{
    text txt = create_text();
    testing::internal::CaptureStderr();
    mcursor(txt, 3, 1);
    show(txt);
    std::string outp = testing::internal::GetCapturedStderr();
    EXPECT_EQ(outp, "There are already no any lines in the text!\n");
    remove_all(txt);
}

TEST(mwbb, outerr)
{
    text txt = create_text();
    testing::internal::CaptureStderr();
    txt = mwbb(txt);
    show(txt);
    std::string outp = testing::internal::GetCapturedStderr();
    EXPECT_EQ(outp, "There are already no any lines in the text!\n");
    remove_all(txt);
}

TEST(show, whoutcur){
    text txt = create_text();
    load(txt, filenm);
    testing::internal::CaptureStdout();
    show(txt);
    std::string out = testing::internal::GetCapturedStdout();
    int i = 0;
    node* current = txt->begin;
    while(current){
        for (int j = 0; j < strlen(current->contents); j++){
            EXPECT_EQ(out[i], current->contents[j]);
            i++;
        }
        if(current != txt->end)
            i++;
        current = current->next;
    }
    EXPECT_EQ(out[i], '|');
    remove_all(txt);
}

TEST(show, whcur){
    text txt = create_text();
        load(txt, filenm);
        mcursor(txt, 1, 2);
        testing::internal::CaptureStdout();
        show(txt);
        std::string output = testing::internal::GetCapturedStdout();
        int i = 1;
        node *current = txt->begin;
        while(current)
        {
            for (int j = 0; j < strlen(current->contents); j++)
            {
                if (current == txt->cursor->line
                       && j == txt->cursor->position)
                {
                    EXPECT_EQ(output[i], '|');
                }
                EXPECT_EQ(output[i], current->contents[j]);
                i++;
            }
            i++;
            current = current->next;
        }
        remove_all(txt);
}

TEST(snempty, conword)
{
    text txt = create_text();
    testing::internal::CaptureStdout();
    load(txt, filenm);
    shownonempty(txt);
    std::string out = testing::internal::GetCapturedStdout();

    // сравниваем значения
    ASSERT_EQ(out, "qwertyASD asdsweASD \nrewvaf1321\n321\n321\n");
    remove_all(txt);
}

TEST(snempty, conspace)
{
   char* fnm = "smptyright.txt";
   text txt = create_text();
   testing::internal::CaptureStdout();
   load(txt, filenm);
   mcursor(txt, 2, 3);
   shownonempty(txt);
   std::string out = testing::internal::GetCapturedStdout();
   ASSERT_EQ(out, "qwe|rtyASD asdsweASD \nrewvaf1321\n321\n321\n");
   remove_all(txt);
}

#endif

#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <setjmp.h>

// redefine assert to set a boolean flag
#ifdef assert
#undef assert
#endif
#define assert(x) (res = res && (x))

mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

// function to test
void copy(char * source, char * dest)
{
	int fd_input, fd_output, rval;
	off_t n_bytes = 0;
	struct stat s_stat = {0};
	
	if ((fd_input = open(source, O_RDONLY)) == -1)
	{
		return -1;
	}
	if ((fd_output = creat(dest, 0660)) == -1)
	{
		close(fd_input);
		return -1;
	}
	
	rval = write(fd_output, fd_input, sizeof(fd_input));

	close(fd_input);
	close(fd_output);
}

// main result return code used by redefined assert
static int res;

// variables controling stub functions
static int expected_code;
static int should_exit;
static jmp_buf jump_env;

// test suite main variables
static int done;
static int num_tests;
static int tests_passed;

//  utility function
void TestStart(char *name)
{
    num_tests++;
    res = 1;
    printf("-- Testing %s ... ",name);
}

//  utility function
void TestEnd()
{
    if (res) tests_passed++;
    printf("%s\n", res ? "success" : "fail");
}

// stub function
void exit(int code)
{
    if (!done)
    {
        assert(should_exit==1);
        assert(expected_code==code);
        longjmp(jump_env, 1);
    }
    else
    {
        _exit(code);
    }
}

// test case 1: Copy file to another file in the same directory
void test_one()
{
    int jmp_rval;
    int r;

    TestStart("test_one");
    should_exit = 0;
    if (!(jmp_rval=setjmp(jump_env)))
    {
        copy("./", "hi.txt");
    }

    assert(jmp_rval==0);
    assert(r==4);
    TestEnd();
}

// test case 2: Make a new directory and copy file to the new directory
void test_two()
{
    int jmp_rval;
    int r;
    char inpath[100] = "./file1.txt";
    char destpath[100] = "./newfile2.txt";

    TestStart("test_two");
    should_exit = 1;
    expected_code = 2;
    if (!(jmp_rval=setjmp(jump_env)))
    {
        mkdir("./testcase2", 0700);
        copy(inpath, destpath);
    }

    assert(jmp_rval==1);
    TestEnd();
}

// test case 3: Overwrite file 
void test_three()
{
    int jmp_rval;
    char inpath[100] = "./file1.txt";
    char destpath[100] = "./file1.txt";

    TestStart("test_three");
    should_exit = 1;
    expected_code = 2;
    if (!(jmp_rval=setjmp(jump_env)))
    {
        copy(inpath, destpath);
    }

    assert(jmp_rval==1);
    TestEnd();
}

// test case 4: Add text to new file
void test_four()
{
    int jmp_rval;
    char msg[100] = "Test 3";
    char inpath[100] = "./file1.txt";
    char destpath[100] = "./newfile3.txt";
    int fd = open(destpath, O_RDWR, mode);

    TestStart("test_four");
    should_exit = 1;
    expected_code = 2;
    if (!(jmp_rval=setjmp(jump_env)))
    {
        copy(inpath, destpath);
        write(fd, msg, sizeof(msg));
    }

    assert(jmp_rval==1);
    TestEnd();
}

int main()
{
    num_tests = 0;
    tests_passed = 0;
    done = 0;
    test_one();
    test_two();
    test_three();
    test_four();
    printf("Total tests passed: %d\n", tests_passed);
    done = 1;
    return !(tests_passed == num_tests);
}
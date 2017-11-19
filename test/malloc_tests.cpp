#include <gtest/gtest.h>
#include "../src/my_malloc.h"

TEST(FreeListTest, PrintList){
    reset_heap();
    print_free_list();
}

TEST(MallocTest, InitAndCheckAvailableMemory) {
    reset_heap();
    size_t size = available_memory();
    ASSERT_EQ(size, HEAP_SIZE - sizeof(node_t));
}

TEST(MallocTest, CheckNumberOfFreeNodes) {
    reset_heap();
    int count = number_of_free_nodes();
    ASSERT_EQ(count, 1);
}

TEST(MallocTest, SimpleMallocCall) {
    reset_heap();
    void *p = my_malloc(100);
    ASSERT_TRUE(p != NULL);
}

TEST(MallocTest, SimpleMallocCallNumberOfFreeNodes) {
    reset_heap();
    void *p = my_malloc(100);
    ASSERT_TRUE(p != NULL);
    int count = number_of_free_nodes();
    ASSERT_EQ(count, 1);
}

TEST(MallocTest, MallocTooMuchMemory) {
    reset_heap();
    void *p = my_malloc(10000);
    ASSERT_TRUE(p == NULL);
}

TEST(MallocTest, SimpleMallocCallCheckAvailableMemory) {
    reset_heap();
    void *p = my_malloc(100);
    ASSERT_TRUE(p != NULL);
    size_t size = available_memory();
    ASSERT_EQ(size, HEAP_SIZE - sizeof(node_t)*2 - 100);
}

TEST(MallocTest, CheckYourHead) {
    reset_heap();
    header_t *p = (header_t *)((char *)my_malloc(100) - sizeof(header_t));
    ASSERT_EQ(p->magic, MAGIC);
}

TEST(MallocTest, SimpleFreeCheck) {
    reset_heap();
    void *p = my_malloc(100);
    void *k = my_malloc(100);
    my_free(p);
    ASSERT_EQ(number_of_free_nodes(), 2);
    k = NULL; // to stop compiler warnings.
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

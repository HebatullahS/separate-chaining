#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define sizeOfFile 784

typedef struct image
{
    int img_arr[sizeOfFile];
}image;
typedef struct data_item
{
    image data;
    int key;
}data_item;

typedef struct {
int flag;
data_item *Tr;
}Table;

Table array[1000];


data_item items[1000];

void readfile()
{
    FILE *f = fopen("MNIST-data(datastructures_assignment3).txt","r");
    int i,j,key;
    image img;
    for(i=0;i<1000;i++)
    {
        array[i].flag=0;

        for(j=0;j<784;j++){
        fscanf(f,"%d",&img.img_arr[j]);
        }
        fscanf(f,"%d",&key);
        put(key,img);

}


    //separated chaining

  struct hash *hashTable = NULL;
  int eleCount = 0;

  struct node {
        int key;
        struct node *next;
  };

  struct hash {
        struct node *head;
        int count;
  };

  struct node * createNode(int key) {
        struct node *newnode;
        newnode = (struct node *)malloc(sizeof(struct node));
        newnode->key = key;
        newnode->next = NULL;
        return newnode;
  }


  void put(int key,image img) {
        int hashIndex = key % eleCount;
        struct node *newnode =  createNode(key);


        if (!hashTable[hashIndex].head) {
                hashTable[hashIndex].head = newnode;
                hashTable[hashIndex].count = 1;
                return;
        }
        /* adding new node to the list */
        newnode->next = (hashTable[hashIndex].head);
        /*
         * update the head of the list and no of
         * nodes in the current bucket
         */
        hashTable[hashIndex].head = newnode;
        hashTable[hashIndex].count++;
        return;
  }


  void delete(int key) {
        /* find the bucket using hash index */
        int hashIndex = key % eleCount, flag = 0;
        struct node *temp, *myNode;
        /* get the list head from current bucket */
        myNode = hashTable[hashIndex].head;
        if (!myNode) {
                printf("Given data is not present in hash Table!!\n");
        }
        temp = myNode;
        while (myNode != NULL) {
                /* delete the node with given key */
                if (myNode->key == key) {
                        flag = 1;
                        if (myNode == hashTable[hashIndex].head)
                                hashTable[hashIndex].head = myNode->next;
                        else
                                temp->next = myNode->next;

                        hashTable[hashIndex].count--;
                        free(myNode);
                        break;
                }
                temp = myNode;
                myNode = myNode->next;
        }
        if (flag)
                printf("Data deleted successfully from Hash Table\n");
        else
                printf("Given data is not present in hash Table!!!!\n");
  }

  void get(int key) {
        int hashIndex = key % eleCount, flag = 0;
        struct node *myNode;
        myNode = hashTable[hashIndex].head;
        if (!myNode) {
                printf("Search element unavailable in hash table\n");
                return;
        }
        while (myNode != NULL) {
                if (myNode->key == key) {
                        printf("Key  : %d\n", myNode->key);


                        flag = 1;
                        break;
                }
                myNode = myNode->next;
        }
        if (!flag)
                printf("Search element unavailable in hash table\n");
        return;
  }


  int main() {

        int n, ch, key;
        printf("Enter the number of elements:");
        scanf("%d", &n);
        eleCount = n;
        /* create hash table with "n" no of buckets */
        hashTable = (struct hash *)calloc(n, sizeof (struct hash));
        while (1) {
                printf("\n1. Insertion\t2. Deletion\n");
                printf("3. Searching\t4. Exit\n");
                printf("Enter your choice:");
                scanf("%d", &ch);
                switch (ch) {
                        case 1:
                                printf("Enter the key value:");
                                scanf("%d", &key);
                                getchar();

                                /*inserting new node to hash table */
                                put(key,img);
                                break;

                        case 2:
                                printf("Enter the key to perform deletion:");
                                scanf("%d", &key);
                                /* delete node with "key" from hash table */
                                delete(key);
                                break;

                        case 3:
                                printf("Enter the key to search:");
                                scanf("%d", &key);
                                get(key);
                                break;
                        case 4:
                                exit(0);
                        default:
                                printf("U have entered wrong option!!\n");
                                break;
                }
        }
        return 0;
  }


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//3
int lengthOfLongestSubstring(char * s){
    int len = strlen(s);
    int max = 0;
    int cnt = 1;
	for (int i=0; i<len-1; ++i) {
		for (int j=i+1; j<len; ++j) {
            if (s[j]==s[i]) {
                cnt = 1;
                printf("max:%d s[%d]=%c\n", max, j, s[j]);
                break;
            } else {
                cnt++;
                max = max>cnt?max:cnt;
            }
	    }
    }
    return max;
}

int main()
{
    char *str = "abcabcbb";
    int len = lengthOfLongestSubstring(str);
    printf("%d\n", len);

    return 0;
}

#if 0
//2
struct ListNode {
    int val;
    struct ListNode *next;
};
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
	struct ListNode *ret = NULL;
	struct ListNode *p;
	int flag = 0; //保存进位
	while (l1 != NULL || l2 != NULL || flag) {
		int a = 0, b = 0, c =0;
		if (l1) {
			a = l1->val;
			l1 = l1->next;
		}
		if (l2) {
			b = l2->val;
			l2 = l2->next;
		}
		c=a+b+flag;
		if (c>=10) {
			c=c-10;
			flag=1;
		} else {
			flag = 0;
		}
/*
		if (a+b>=10) {
			c = a+b-10 + flag;
			flag = 1;
		} else {
			c = a+b+flag;
			flag = 0;
		}
*/
		struct ListNode *newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
		newNode->val = c;
		newNode->next = NULL;
		if (!ret) {
			ret = newNode;
			p = ret;
		} else {
			p->next = newNode;
			p = p->next;
		}
	}
	return ret;
}
#endif

//1
#if 0
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    int a=-1,b=-1;
    int *ret = (int*)malloc(sizeof(int)*2);
    int i,j;
    for(i=0; i<numsSize-1; ++i) {
        for(j=i+1; j<numsSize; ++j) {
            printf("%d + %d = %d\n", nums[i], nums[j], nums[i]+nums[j]);
            if(nums[i] + nums[j] == target) {
                a=i;
                b=j;
            }
        }
    }
    ret[0] = a;
    ret[1] = b;
    *returnSize = 2;
    return ret;
}

int main(int argc, char* argv[])
{
	int nums[] = {-1,-2,-3,-4,-5};
	int returnSize;
	int *ret = twoSum(nums, 5, -8, &returnSize);
	int i;
	for (i = 0; i<returnSize; ++i) {
		printf("%d ", ret[i]);
	}
	printf("\n");

	return 0;
}
#endif


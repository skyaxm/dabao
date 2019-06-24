#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//4
//时间复杂度为 O(log(m + n))=O(logm + logn)
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
	int *nums3 = (int *)calloc(nums1Size+nums2Size, 1);
	int i=0,j=0;
	while(i<nums1Size||j<nums2Size) {
		if (nums1[i])
	}
}


#if 0
//3
/*
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len=0;//存放结果
        int start=0;//存放起始查找位置
        string str="";//存放无重复字符子串
        for(int i=0;i<s.length();i++)
        {
            if(str.find(s[i])==-1)//未找到重复字符，放入str
                str=str+s[i];
            else //找到重复子串
            {
                len=len>str.length()?len:str.length();//更改最大字串长度
                i=s.find_first_of(s[i],start);//从第start位置开始找s[i]
                start=i+1;//下一次查找开始的位置
                str="";//还原str
            }
        }
        len=len>str.length()?len:str.length();
        return len;
    }
};
class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		int m[256]={0};//字符有256个
		int left=0;//查找的左边界
		int mlen=0;//结果
		for(int i=0;i<s.length();i++)
		{
			if(m[s[i]]==0||m[s[i]]<left)
			{
				mlen=max(mlen,i-left+1);
			}
			else
			{
				left=m[s[i]];
			}
			m[s[i]]=i+1;
		}
		return mlen;
	}
};
注解：
查找范围：left到i之间的字符串
m[s[i]]=0代表该字符s[i]未出现过
若m[s[i]]!=0，则m[s[i]]当前的大小代表字符s[i]再次出现时应该查找的起始位置，对应left的值
若m[s[i]]<left说明字符s[i]上一次出现的位置不在当前的查找范围
*/
int lengthOfLongestSubstring(char * s){
    int len = strlen(s);
    int max = 0;
    int left = 0; //string left board
	int next[256] = {0}; //if the char repeat next search position
	for (int i=0; i<len; ++i) {
		if(next[s[i]] == 0 || next[s[i]] < left) {
			max = max>(i-left+1)?max:(i-left+1);
		} else {
			left = next[s[i]];
		}
		next[s[i]] = i+1;
    }
    return max;
}

int main()
{
//	char *str = "aab"; //2
    char *str = "dvdf";//output:df the next search position error
    int len = lengthOfLongestSubstring(str);
    printf("%d\n", len);

    return 0;
}
#endif

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


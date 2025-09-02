# 题目信息

# TMT Document

## 题目描述

The student council has a shared document file. Every day, some members of the student council write the sequence TMT (short for Towa Maji Tenshi) in it.

However, one day, the members somehow entered the sequence into the document at the same time, creating a jumbled mess. Therefore, it is Suguru Doujima's task to figure out whether the document has malfunctioned. Specifically, he is given a string of length $ n $ whose characters are all either T or M, and he wants to figure out if it is possible to partition it into some number of disjoint subsequences, all of which are equal to TMT. That is, each character of the string should belong to exactly one of the subsequences.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero) characters.

## 说明/提示

In the first test case, the string itself is already a sequence equal to TMT.

In the third test case, we may partition the string into the subsequences TMTMTT. Both the bolded and the non-bolded subsequences are equal to TMT.

## 样例 #1

### 输入

```
5
3
TMT
3
MTT
6
TMTMTT
6
TMTTTT
6
TTMMTT```

### 输出

```
YES
NO
YES
NO
YES```

# AI分析结果

### 题目内容
# TMT文档

## 题目描述
学生会有一个共享文档文件。每天，学生会的一些成员会在里面写入序列TMT（Towa Maji Tenshi的缩写）。
然而，有一天，成员们不知怎么地同时将序列输入到文档中，造成了混乱。因此，道岛秀uru的任务是弄清楚文档是否出了故障。具体来说，他会得到一个长度为$n$的字符串，其字符全部为T或M，他想弄清楚是否有可能将其划分为若干个不相交的子序列，所有子序列都等于TMT。也就是说，字符串中的每个字符都应恰好属于其中一个子序列。
字符串$a$是字符串$b$的子序列，如果$a$可以通过删除$b$中的几个（可能为零个）字符得到。

## 说明/提示
在第一个测试用例中，字符串本身已经是一个等于TMT的序列。
在第三个测试用例中，我们可以将字符串划分为子序列TMTMTT。加粗和非加粗的子序列都等于TMT。

## 样例 #1
### 输入
```
5
3
TMT
3
MTT
6
TMTMTT
6
TMTTTT
6
TTMMTT
```
### 输出
```
YES
NO
YES
NO
YES
```
• **算法分类**：字符串
• **综合分析与结论**：这些题解的核心思路都是基于判断字符串中T和M的数量关系以及位置分布来确定能否分割成若干个TMT子序列。大多数题解通过正反两次遍历字符串，确保每个M的前后都有足够数量的T，同时满足T的总数是M总数的2倍。各题解的主要差异在于实现细节和代码风格，部分题解使用前缀和优化判断过程，部分则直接通过计数变量进行判断。
• **所选的题解**：
  - **作者：Daidly (赞：16)  星级：4星**
    - **关键亮点**：思路清晰简洁，通过正反两次遍历字符串，实时比较T和M的数量，若在某一时刻T的数量小于M的数量，则完不成匹配，最后再结合T和M的总数关系判断。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,numT,numM,f=1;
string a;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>a;a=" "+a;
        for(int i=1;i<=n;++i){
            if(a[i]=='T')numT++;
            if(a[i]=='M')numM++;
            if(numT<numM){f=0;break;}
        }numT=0,numM=0;
        for(int i=n;i>=1;--i){
            if(a[i]=='T')numT++;
            if(a[i]=='M')numM++;
            if(numT<numM){f=0;break;}
        }
        if(f==0||numT!=numM*2)puts("NO");
        else puts("YES");
        numT=0,numM=0,f=1;
    }
    return 0;
}
```
    - **核心实现思想**：先从前往后遍历字符串，统计T和M的数量并比较，若T的数量小于M则标记为不可行；再从后往前重复此操作，最后根据标记和T、M总数关系输出结果。
  - **作者：Night_sea_64 (赞：3)  星级：4星**
    - **关键亮点**：利用前缀和维护T的数量，从而快速判断每个M前后T和M的数量关系，优化了判断过程。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int a[100010];//前缀和数组
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        bool flag=1;
        string s;
        cin>>n>>s;
        for(int i=0;i<n;i++)
            a[i+1]=a[i]+(s[i]=='T');//记录前缀和。如果等于T就加上1个。
        for(int i=0;i<n;i++)
            if(s[i]=='M')
                if(a[i+1]<i+1-a[i+1]||a[n]-a[i]<n-i-a[n]+a[i])
                {
                    flag=0;
                    break;
                }
                //a[i+1]是前面T的个数，a[n]-a[i]是后面T的个数。
                //i+1-a[i+1]是前面的M的个数，n-i-a[n]+a[i]是后面的M的个数。
        if(flag&&(n-a[n])*2==a[n])cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
        //n-a[n]是M的总个数，a[n]是T的总个数。
    }
    return 0;
}
```
    - **核心实现思想**：先通过循环构建前缀和数组记录T的数量分布，然后遍历字符串，对于每个M，通过前缀和数组判断其前后T和M的数量是否满足要求，最后结合T和M的总数关系输出结果。
  - **作者：badFlamesへ (赞：3)  星级：4星**
    - **关键亮点**：通过分析样例总结出对于从左往右的第$i$个M，它的左边必须要有$i$个T，右边必须要有$n - i + 1$个T的规律，然后通过两次遍历字符串进行判断。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;

int t, n;
string s;
int cnt_t, cnt_m, len;//T的个数，M的个数，字符串长度

inline bool check() {//检查字符串的函数
    cnt_t = cnt_m = 0;
    for(int i = 0; i < len; i++) {//正着统计T与M的实时关系
        if(s[i] == 'T') cnt_t++;
        if(s[i] == 'M') cnt_m++;
        if(cnt_t < cnt_m) return false;//发现不符合上述关系就直接false
    }
    if(cnt_t!= 2 * cnt_m) return false;//T与M的数量不匹配也直接false
    cnt_t = cnt_m = 0;
    for(int i = n - 1; i >= 0; i--) {//反着来一遍
        if(s[i] == 'T') cnt_t++;
        if(s[i] == 'M') cnt_m++;
        if(cnt_t < cnt_m) return false;
    }
    return true;//返回true
}

signed main() {
    cin >> t;
    while(t--) {
        cin >> n >> s;
        len = s.length();
        if(check()) puts("YES");//输出结果
        else puts("NO");
    }
}
```
    - **核心实现思想**：定义检查函数，在函数中通过正反两次遍历字符串，分别统计T和M的数量并比较，同时结合T和M的总数关系进行判断，主函数中调用检查函数输出结果。
• **最优关键思路或技巧**：利用正反两次遍历字符串来确保每个M的前后都有足够的T，同时结合T和M的总数关系进行判断。部分题解使用前缀和优化判断过程，能更高效地获取特定位置前后T和M的数量。
• **可拓展之处**：同类型题可考察对其他特定子序列的匹配判断，类似算法套路是通过分析子序列特征，找到字符数量和位置关系的规律，利用遍历和计数等方式进行判断。
• **相似知识点洛谷题目**：
  - [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
  - [P2219 [HAOI2007] 紧急疏散EVACUATE](https://www.luogu.com.cn/problem/P2219)
  - [P3376 【模板】网络最大流](https://www.luogu.com.cn/problem/P3376)
• **个人心得摘录总结**：部分作者提到一开始思路局限于单纯统计字符个数，但通过分析样例发现仅统计个数无法满足要求，从而进一步思考得出正确思路。这表明在解题时不能仅依赖初步想法，要通过样例深入挖掘题目隐藏条件和规律。 

---
处理用时：78.55秒
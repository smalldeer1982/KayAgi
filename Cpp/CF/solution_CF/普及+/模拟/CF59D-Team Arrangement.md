# Team Arrangement

## 题目描述

Recently personal training sessions have finished in the Berland State University Olympiad Programmer Training Centre. By the results of these training sessions teams are composed for the oncoming team contest season. Each team consists of three people. All the students of the Centre possess numbers from $ 1 $ to $ 3n $ , and all the teams possess numbers from $ 1 $ to $ n $ . The splitting of students into teams is performed in the following manner: while there are people who are not part of a team, a person with the best total score is chosen among them (the captain of a new team), this person chooses for himself two teammates from those who is left according to his list of priorities. The list of every person's priorities is represented as a permutation from the rest of $ 3n-1 $ students who attend the centre, besides himself.

You are given the results of personal training sessions which are a permutation of numbers from $ 1 $ to $ 3n $ , where the $ i $ -th number is the number of student who has won the $ i $ -th place. No two students share a place. You are also given the arrangement of the already formed teams in the order in which they has been created. Your task is to determine the list of priorities for the student number $ k $ . If there are several priority lists, choose the lexicographically minimal one.

## 样例 #1

### 输入

```
3
5 4 1 2 6 3 7 8 9
5 6 2
9 3 4
1 7 8
4
```

### 输出

```
2 3 5 6 9 1 7 8 ```

## 样例 #2

### 输入

```
3
5 4 1 2 6 3 7 8 9
5 6 2
9 3 4
1 7 8
8
```

### 输出

```
1 2 3 4 5 6 7 9 ```

## 样例 #3

### 输入

```
2
4 1 3 2 5 6
4 6 5
1 2 3
4
```

### 输出

```
5 6 1 2 3 ```

# 题解

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2000}$
---
### 解题思路：

愚蠢的阅读理解题。

给出的第一个序列的数值是人，下标是人的排名。所以每一次直接取第一个不在队伍里人，让这个人作为队长选人就行了。

要求的是让你求出一个给定的一个人选人的优先级，这个人按照优先级往下选能选出给出的那个团队组合（如果这个人已经被选了就跳过），同时要求字典序最小。

那么如果这个人不能选人，那么怎么安排优先级都是无所谓的（换句话说，受是没有主动权的），直接输出所有可能的中字典序最小的 $1,2,3...$ 就行了。

否则这个人就是队长，将其它之前就已经确定好的队伍里的人放入优先级的考虑中不会影响最后的选择，所以当还有队员未被选择时，将字典序小的那些已经被选择的人选进去能降低字典序。而当所有的队员都被选了，再将之前的那些放进去就反而会升高字典序，直接按顺序输出就行了。

注意不要把要求的 $k$ 放进去。

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=300005;
int n,x,y,z,t[MAXN],te[MAXN],k,ch[MAXN],pre[MAXN],suf[MAXN],cnt1,cnt2,cnt3;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=3*n;i++)scanf("%d",&t[i]);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&x,&y,&z);
		te[x]=te[y]=te[z]=i;
	}
	scanf("%d",&k);
	for(int i=1;i<=3*n;i++){
		if(t[i]==k){
			if(ch[te[k]]==1){
				for(int j=1;j<=3*n;j++)if(j!=k)printf("%d ",j);
				return 0-0;
			}
			ch[te[k]]=1;
			break;
		}
		ch[te[t[i]]]=1;
	}
	for(int i=1;i<=3*n;i++){
		if(i==k)continue;
		if(cnt3==2){
			suf[++cnt2]=i;
			continue;
		}
		if(te[i]==te[k])cnt3++;
		if(ch[te[i]]==1)pre[++cnt1]=i;
		else suf[++cnt2]=i;
	}
	for(int i=1;i<=cnt1;i++)printf("%d ",pre[i]);
	for(int i=1;i<=cnt2;i++)printf("%d ",suf[i]);
	printf("\n");
	return 0;
}
```



---

## 作者：Frather_ (赞：0)

## **扯淡**

~~其实这题真的没啥。。。~~

毕竟题面是窝翻译的，不把这题做了都不好意思了~

## **思路**

~~真的很水~~

直接枚举即可。

寻找队长，如果是 $k$, 那就为其找队员；如果不是 $k$， 那就顺序输出 $1-n$。

更多解析已经写在代码里了。

话说越简单的题出错率越高正常么。。。

踩坑记录：

由于变量名写错写重及某些原因的神笔错误

![](https://img.imgdb.cn/item/605737088322e6675cf4273e.jpg)

## **CODE**

```cpp
/*

代码存在明显错误~

Name: CF59D Team Arrangement

Solution: 瞎搞

By Frather_

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#define InF 0x3f3f3f3f
#define kMax 10e5
#define kMin -10e5
#define kMod 998244353
using namespace std;
/*===================================================快读*/
//手动放抄袭
/*===============================================定义变量*/
int n;

const int _ = 1000010;

int t[_];
queue<int> q;//利用 队列 记录当前剩余的学生的得分

struct team
{
    int fir;
    int sec;
    int tir;
} tm[_];//记录每个团队的三位成员
int head[_];

int k;

int sum;
int flag[_],flag_[_];
int num;
/*=============================================自定义函数*/

/*=================================================主函数*/
int main()
{
    n = read();
    for (int i = 1; i <= n * 3; i++)
    {
        t[i] = read();
        q.push(t[i]);//将当前同学的得分添加进队列
    }
    for (int i = 1; i <= n; i++)//存储给定团队的成员
    {
        tm[i].fir = read();
        tm[i].sec = read();
        tm[i].tir = read();
    }

    k = read();
    for (int i = 1; i <= n; i++)
    {
        if (q.front() == k)//当前得分的同学是第 k 位同学
        {
            sum = i;//记录编号
            break;
        }
        q.pop();
        flag[tm[i].sec] = 1;
        flag[tm[i].tir] = 1;

        if (!q.empty())
            while (flag[q.front()] == 1)
            {
                q.pop();
                if (q.empty())
                    break;
            }
    }


    if (sum == 0)//如果 k 不是队长，顺序输出 1 ~ n
    {
        for (int i = 1; i <= n * 3; i++)
            if (i != k)
                printf("%d ", i);
        puts("");
        return 0;
    }
    //如果 k 是队长
    for (int i = 1; i <= sum; i++)//为k寻找队员
    {
        flag_[tm[i].fir]++;
        flag_[tm[i].sec]++;
        flag_[tm[i].tir]++;
    }
    if (tm[sum].fir != k && tm[sum].fir > num)
        num = tm[sum].fir;
    if (tm[sum].sec != k && tm[sum].sec > num)
        num = tm[sum].sec;
    if (tm[sum].tir != k && tm[sum].tir > num)
        num = tm[sum].tir;

    for (int i = 1; i <= num; i++)//按字典序顺序输出除第 k 个学生外的最小排列
        if (flag_[i] && i != k)
        {
            flag_[i] = 2;
            printf("%d ", i);
        }
    for (int i = 1; i <= n * 3; i++)
        if (flag_[i] != 2 && i != k)
            printf("%d ", i);
    puts("");

    return 0;
}
```

---


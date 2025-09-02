# Dynamic Problem Scoring

## 题目描述

Vasya 和 Petya 参加了一场 Codeforces 编程比赛。这场比赛持续两个小时，共有五道题目。

比赛采用动态计分系统。题目的最高分与你解题的难度有关，具体是根据解决这道题目的人数占总参赛人数的比例来决定的。只要选手有过一次提交，就被视为参赛者。

！[](https://cdn.luogu.com.cn/upload/vjudge_pic/CF773B/a0f85cbd533a46bf976e07f7a2f9ea90ac93ff77.png)

注意分数区间。例如，有 40 名选手参加比赛，其中 10 人解出某个题目，那么解题比例为 $1/4$，该题目最大分数为 1500 分。

如果题目的最大分数为 $x$，那么从比赛开始到选手正确提交的每分钟，选手都会扣除 $x/250$ 分。例如，题目最大分数是 2000 分，而选手在第 40 分钟提交了答案，那么他将得到 $2000 \times (1 - 40/250) = 1680$ 分。

参赛有 $n$ 位选手，其中包括 Vasya 和 Petya。每位选手对每道题目的提交时间已知，并以分钟为单位记录；如果某题未被解出，则时间记为 -1。

比赛即将结束时，所有选手的提交都通过了预测试，并且没有人尝试黑客攻击。Vasya 认为在最后的两秒钟里不会有新的提交，也没有任何黑客行为，所有提交均会通过系统检测。

然而，Vasya 是个作弊者。他为这场比赛注册了 $10^9 + 7$ 个新账号。Vasya 可以利用这些新账号改变题目的最大分值，提交错误的或者已经解决的题目。需要注意的是，对于未解的题目，他不能提交正确的答案。

Vasya 希望通过这种方式让自己的总得分比 Petya 高。尽管他已经准备好了快速提交脚本，但他不想让作弊行为太过明显，所以希望用尽量少的新账号实现目标。

请你帮 Vasya 找出他需要用多少个新账号才能超越 Petya，或者告诉他如果无法实现这一目标。

## 说明/提示

在第一个示例中，Vasya 的优化策略是利用两个新账号提交最后三道题。这样前两道题的最高分为 1000 分，后三道各为 500 分。Vasya 的总分将是 $980 + 940 + 420 + 360 + 270 = 2970$ 分，而 Petya 为 $800 + 820 + 420 + 440 + 470 = 2950$ 分。

在第二个示例中，Vasya 需用两个新账号的单次失败提交，再用第三个账号的正确提交解决第一道题。这样，所有题目的最高分依次为 500、1500、1000、1500、3000 分。Vasya 最终得分为 2370 分，而 Petya 得分为 2294 分。

在第三个示例中，Vasya 可以借助 27 个新账号为前四道题提交答案，从而让题目变得为 500、500、500、500、2000 分。因第五题的高分，Vasya 能以此战胜仅解出前四题但未能解出第五题的 Petya。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
5 15 40 70 115
50 45 40 30 15
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
55 80 10 -1 -1
15 -1 79 60 -1
42 -1 13 -1 -1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
5
119 119 119 119 119
0 0 0 0 -1
20 65 12 73 77
78 112 22 23 11
1 78 60 111 62
```

### 输出

```
27
```

## 样例 #4

### 输入

```
4
-1 20 40 77 119
30 10 73 50 107
21 29 -1 64 98
117 65 -1 -1 -1
```

### 输出

```
-1
```

# 题解

## 作者：dead_X (赞：0)

## 前言
看到垃圾题应该怎么办呢？当然是给大家一起做啦！
## 思路
注意到 Vasya 在开小号解题之后，每个题不同的分数情况只有 $6^5=46656$ 种，于是我们直接对于每种情况暴力枚举。

钦定每个题的得分情况后，你觉得是要用高明算法求出最少账号数了？

并不，注意到 $n\leq120$ 而得分最高的一档只有 $\frac{1}{32}$，所以我们只要开 $32\times 120$ 个小号就一定能精准控分。

于是，我们继续依次枚举使用的账号数 $t$，算出再多开 $t$ 个账号能不能精准控分。计算再多开出 $t$ 个账号后能控到分的区间和可能达到的区间是否相交即可。

细节不多但是码量很大。

时间复杂度 $6^5\times32\times 5\times n=O(n)$（迫真）。
## 代码
事实上实现有问题，虽然能过，但是可以被叉掉。

反正也没人会去写这个垃圾题吧？

```cpp
// Problem: B. Dynamic Problem Scoring
// Contest: Codeforces - Codeforces Round #412 (rated, Div. 1, based on VK Cup 2017 Round 3)
// URL: https://codeforces.com/contest/806/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//愿神 zhoukangyang 指引我。
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
struct node
{
	int a,b,c,d,e;
}pp[1000003];
int A,B,C,D,E;
const int p[]={-1,1,1,1,1,1,1};
const int q[]={1,32,16,8,4,2,1};
int t[13];
namespace solve
{
	bool cmp(int x,int y,int z,int w)//frac a>frac b
	{
		if(z==-1) return 0;
		return x*w<y*z;
	}
	bool ccmp(int x,int y,int z,int w)//frac a>frac b
	{
		if(z==-1) return 0;
		return x*w<=y*z;
	}
	int qwq(int l,int r,int n,int op){
			if(op==0)if(ccmp(r,n,p[op],q[op])||cmp(p[op+1],q[op+1],l,n)) return 0;
			if(op!=0)if(ccmp(r,n,p[op],q[op])||cmp(p[op+1],q[op+1],l,n)) return 0;
			return 1;
	}
};
const int s[]={3000,2500,2000,1500,1000,500};
signed main()
{
	int n=read();
	for(int i=1; i<=n; i++) 
	{
		pp[i].a=read(),pp[i].b=read(),pp[i].c=read(),pp[i].d=read(),pp[i].e=read();
		if(pp[i].a!=-1) ++A;
		 if(pp[i].b!=-1) ++B;
		 if(pp[i].c!=-1) ++C;
		 if(pp[i].d!=-1) ++D;
		 if(pp[i].e!=-1) ++E;
	}
	int ans=1000000008;
	for(t[0]=0; t[0]<6; t[0]++)
	for(t[1]=0; t[1]<6; t[1]++)
	for(t[2]=0; t[2]<6; t[2]++)
	for(t[3]=0; t[3]<6; t[3]++)
	for(t[4]=0; t[4]<6; t[4]++)
	{
		int d=0;
		//printf("%lld\n",S);
		if(pp[1].a!=-1) d+=s[t[0]]-s[t[0]]/250*pp[1].a;
		if(pp[1].b!=-1) d+=s[t[1]]-s[t[1]]/250*pp[1].b;
		if(pp[1].c!=-1) d+=s[t[2]]-s[t[2]]/250*pp[1].c;
		if(pp[1].d!=-1) d+=s[t[3]]-s[t[3]]/250*pp[1].d;
		if(pp[1].e!=-1) d+=s[t[4]]-s[t[4]]/250*pp[1].e;
		if(pp[2].a!=-1) d-=s[t[0]]-s[t[0]]/250*pp[2].a;
		if(pp[2].b!=-1) d-=s[t[1]]-s[t[1]]/250*pp[2].b;
		if(pp[2].c!=-1) d-=s[t[2]]-s[t[2]]/250*pp[2].c;
		if(pp[2].d!=-1) d-=s[t[3]]-s[t[3]]/250*pp[2].d;
		if(pp[2].e!=-1) d-=s[t[4]]-s[t[4]]/250*pp[2].e;
		if(d>0) 
		{
			for(int j=0; j<=4000; ++j)
			{
				int f=0;
				if(solve::qwq(A,A+(j*(pp[1].a!=-1)),n+j,t[0])) ++f;
				if(solve::qwq(B,B+(j*(pp[1].b!=-1)),n+j,t[1])) ++f;
				if(solve::qwq(C,C+(j*(pp[1].c!=-1)),n+j,t[2])) ++f;
				if(solve::qwq(D,D+(j*(pp[1].d!=-1)),n+j,t[3])) ++f;
				if(solve::qwq(E,E+(j*(pp[1].e!=-1)),n+j,t[4])) ++f;
				if(f==5)
				{
					// if(j==1)
					// printf("%lld\n",d),
					// printf("%lld %lld %lld %lld %lld\n",t[0],t[1],t[2],t[3],t[4]),
					// printf("%lld %lld %lld %lld\n",D,D+(j*(pp[1].d!=-1)),n+j,t[3]);
					ans=min(ans,j);
					break;
				}
			}
		}
	}
	if(ans==1000000008) puts("-1");
	else printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：lenaalyth (赞：0)

暴力+贪心，这题思维难度感觉不是很高（然而我还是一写一bug。。。果然太菜了。。），由题意可知题数等于5，而每个题的等级只有六种，可以直接枚举每个题的分数进行计算比较一下两人分数的高低，然乎分数判断大小一下，若大于后判断与计算一下是否可以凑出该人数以及最小值即可，详情看代码
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int a[500][100],b,d,e,f,ans1=1000000,ans;
int m,n,c[110][110],v[100];
int p[10]= {0,500,1000,1500,2000,2500,3000},dd[10]= {0,1,2,4,8,16,32};
int chuli(int xx,int yy,int ren) {
    if(v[xx]*dd[yy]<=n+ren&&(v[xx]*dd[yy+1]>n+ren)/*||(v[xx]==0&&yy==6))*/)
	{
//	    cout<<xx<<" "<<yy+1<<v[xx]*dd[yy+1]<<" "<<n<<endl;
	    return 0;
	}
	else if(v[xx]*dd[yy]<=n+ren&&(v[xx]==0&&yy==6))
    {
  //      cout<<xx<<" "<<yy<<endl;
        return 0;
    }
	else if(c[1][xx]==-1&&v[xx]*dd[yy]<=n+ren)
    {
    return 1000000;
    }
	else if(v[xx]*dd[yy]>=n+ren) {
		return v[xx]*dd[yy]-n-ren;
	}
	else if(v[xx]*dd[yy+1]<=n+ren)
	{
		for(int x=1; x<=ren; x++) {
			if((v[xx]+x)*dd[yy+1]>n+ren) {
				return 0;
			}
		}
		int l1=1,r1=3600,mid;
		while(l1<r1-1)
        {
            mid=(l1+r1);
            if(v[xx]+mid+ren*dd[yy+1]<=n+mid+ren)
            {
            l1=mid;
            }
            else
            {
            r1=mid;
            }
        }
        mid=r1-1;
        if(v[xx]+mid+ren*dd[yy+1]<=n+mid+ren)
        {
            r1--;
        }
        mid=r1-1;
        if(v[xx]+mid+ren*dd[yy+1]<=n+mid+ren)
        {
            r1--;
        }
        return r1;
	}
	return 0;
}
int main() {
	cin>>n;
	for(int x=1; x<=n; x++) {
		for(int y=1; y<=5; y++) {
			cin>>a[x][y];
			if(a[x][y]!=-1)
			{
                v[y]++;
			}
		}
		if(x==1) {
			if(a[1][1]!=-1) {
				c[1][1]=251-1-a[1][1];
			}
			else{c[1][1]=-1;}
			if(a[1][2]!=-1) {
				c[1][2]=251-1-a[1][2];
			}
			else{c[1][2]=-1;}
			if(a[1][3]!=-1) {
				c[1][3]=251-1-a[1][3];
			}
			else{c[1][3]=-1;}
			if(a[1][4]!=-1) {
				c[1][4]=251-1-a[1][4];
			}
			else{c[1][4]=-1;}
			if(a[1][5]!=-1) {
				c[1][5]=251-1-a[1][5];
			}
			else{c[1][5]=-1;}
		} else if(x==2) {
			if(a[2][1]!=-1) {
				c[2][1]=251-1-a[2][1];
			}
			else{c[2][1]=-1;}
			if(a[2][2]!=-1) {
				c[2][2]=251-1-a[2][2];
			}
			else{c[2][2]=-1;}
			if(a[2][3]!=-1) {
				c[2][3]=251-1-a[2][3];
			}
			else{c[2][3]=-1;}
			if(a[2][4]!=-1) {
				c[2][4]=251-1-a[2][4];
			}
			else{c[2][4]=-1;}
			if(a[2][5]!=-1) {
				c[2][5]=251-1-a[2][5];
			}
			else{c[2][5]=-1;}
		}
	}
	for(int x1=1; x1<=6; x1++) {
		for(int x2=1; x2<=6; x2++) {
			for(int x3=1; x3<=6; x3++) {
				for(int x4=1; x4<=6; x4++) {
					for(int x5=1; x5<=6; x5++) {
							long long zhi1=0,zhi2=0;
							if(c[1][1]!=-1) {
								zhi1+=(p[x1]/250)*c[1][1];
							}
							if(c[1][2]!=-1) {
								zhi1+=(p[x2]/250)*c[1][2];
							}
							if(c[1][3]!=-1) {
								zhi1+=(p[x3]/250)*c[1][3];
							}
							if(c[1][4]!=-1) {
								zhi1+=(p[x4]/250)*c[1][4];
							}
							if(c[1][5]!=-1) {
								zhi1+=(p[x5]/250)*c[1][5];
							}
							if(c[2][1]!=-1) {
								zhi2+=(p[x1]/250)*c[2][1];
							}
							if(c[2][2]!=-1) {
								zhi2+=(p[x2]/250)*c[2][2];
							}
							if(c[2][3]!=-1) {
								zhi2+=(p[x3]/250)*c[2][3];
							}
							if(c[2][4]!=-1) {
								zhi2+=(p[x4]/250)*c[2][4];
							}
							if(c[2][5]!=-1) {
								zhi2+=(p[x5]/250)*c[2][5];
							}
							if(zhi1>zhi2) {
                                ans=0;
								ans+=chuli(1,x1,ans);
								if(ans1<ans)
                                {
                                    break;
                                }
								ans+=chuli(2,x2,ans);
								if(ans1<ans)
                                {
                                    break;
                                }
								ans+=chuli(3,x3,ans);
								if(ans1<ans)
                                {
                                    break;
                                }ans+=chuli(4,x4,ans);
								if(ans1<ans)
                                {
                                    break;
                                }ans+=chuli(5,x5,ans);
                                ans1=min(ans,ans1);
 
							}
					}
				}
			}
		}
	}
	if(ans1!=1000000)
	{
	    cout<<ans1<<endl;
	}
	else
    {
	    cout<<-1<<endl;
    }
}
```
。。。这简单粗暴的if和循环看的贼舒服。。。。

---


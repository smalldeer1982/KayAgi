# Colored Boots

## 题目描述

There are $ n $ left boots and $ n $ right boots. Each boot has a color which is denoted as a lowercase Latin letter or a question mark ('?'). Thus, you are given two strings $ l $ and $ r $ , both of length $ n $ . The character $ l_i $ stands for the color of the $ i $ -th left boot and the character $ r_i $ stands for the color of the $ i $ -th right boot.

A lowercase Latin letter denotes a specific color, but the question mark ('?') denotes an indefinite color. Two specific colors are compatible if they are exactly the same. An indefinite color is compatible with any (specific or indefinite) color.

For example, the following pairs of colors are compatible: ('f', 'f'), ('?', 'z'), ('a', '?') and ('?', '?'). The following pairs of colors are not compatible: ('f', 'g') and ('a', 'z').

Compute the maximum number of pairs of boots such that there is one left and one right boot in a pair and their colors are compatible.

Print the maximum number of such pairs and the pairs themselves. A boot can be part of at most one pair.

## 样例 #1

### 输入

```
10
codeforces
dodivthree
```

### 输出

```
5
7 8
4 9
2 2
9 10
3 1
```

## 样例 #2

### 输入

```
7
abaca?b
zabbbcc
```

### 输出

```
5
6 5
2 3
4 6
7 4
1 2
```

## 样例 #3

### 输入

```
9
bambarbia
hellocode
```

### 输出

```
0
```

## 样例 #4

### 输入

```
10
code??????
??????test
```

### 输出

```
10
6 2
1 6
7 3
3 5
4 8
9 7
5 1
2 4
10 9
8 10
```

# 题解

## 作者：Ousmane_Dembele (赞：1)

一道水水的模拟题，“？”是最重要的，先匹配非“？”再分别匹配“？”和对面的非“？”最后匹配“？”和对面的“？”
```
#include<bits/stdc++.h>
using namespace std;
int n,answ;
char s1[150001],s2[150001];
int ans[500000][3];
struct node{
    int d[150001];
    int cnt;
}a[30],b[30];
int main(){
   cin>>n;
   cin>>s1+1>>s2+1;
   for(int i=1;i<=n;i++){
      if(s1[i]=='?')a[0].d[++a[0].cnt]=i;//记录“？”
      else a[s1[i]-'a'+1].d[++a[s1[i]-'a'+1].cnt]=i;
      if(s2[i]=='?')b[0].d[++b[0].cnt]=i;
      else b[s2[i]-'a'+1].d[++b[s2[i]-'a'+1].cnt]=i;
   }
   for(int i=1;i<=26;i++){//挨个匹配非？
       while(a[i].cnt&&b[i].cnt){
            answ++;
            ans[answ][1]=a[i].d[a[i].cnt];
            ans[answ][2]=b[i].d[b[i].cnt];
            a[i].cnt--;
            b[i].cnt--;
       }
   }  
   //匹配一方的？和对方的非？
   for(int i=1;i<=26&&a[0].cnt;i++){
       while(a[0].cnt&&b[i].cnt){
           answ++;
           ans[answ][1]=a[0].d[a[0].cnt];
           ans[answ][2]=b[i].d[b[i].cnt];
           a[0].cnt--;
           b[i].cnt--;
       }
   }
    for(int i=1;i<=26&&b[0].cnt;i++){
       while(b[0].cnt&&a[i].cnt){
           answ++;
           ans[answ][1]=a[i].d[a[i].cnt];
           ans[answ][2]=b[0].d[b[0].cnt];
           a[i].cnt--;
           b[0].cnt--;
       }
   }
   //匹配”？“和”？“
   while(a[0].cnt&&b[0].cnt){
        answ++;
        ans[answ][1]=a[0].d[a[0].cnt];
        ans[answ][2]=b[0].d[b[0].cnt];
        a[0].cnt--;
        b[0].cnt--;
   }
   cout<<answ<<endl;
   for(int i=1;i<=answ;i++){
       printf("%d %d\n",ans[i][1],ans[i][2]);
   }
}
```


---

## 作者：little_sun (赞：1)

贪心裸题

首先'?'肯定不能浪费

所以我们先把'a'-'z'配对

然后再把l中的'?'与r中的（剩下的）'a'-'z'配对

然后再把r中的'?'与l中的（剩下的）'a'-'z'配对

最后再把l中的'?'与r中的'?'配对

然后就做完了

什么？你问怎么输出方案？你记录每一种字母出现的位置不就好了吗？

```cpp
#include <bits/stdc++.h>
#define R register
#define ll long long
#define cmin(a, b) ((a < b) ? a : b)
#define cmax(a, b) ((a < b) ? b : a)
std::string l, r;
int n, m, a[30], b[30];
std::vector<int> ans[2];
std::queue<int> vec[30][2];
int main()
{
    scanf("%d", &n);
    std::cin >> l >> r;
    for (int i = 0; i < n; i++)
    {
        if (l[i] == '?')
            ++a[0], vec[0][0].push(i+1);
        else
            ++a[l[i] - 'a' + 1], vec[l[i] - 'a' + 1][0].push(i+1);
    }
    for (int i = 0; i < n; i++)
    {
        if (r[i] == '?')
            ++b[0], vec[0][1].push(i+1);
        else
            ++b[r[i] - 'a' + 1], vec[r[i] - 'a' + 1][1].push(i+1);
    }
    m = n;
    for (int i = 1; i <= 26; i++)
    {
        while (a[i] && b[i])
        {
            --a[i], --b[i];
            ans[0].push_back(vec[i][0].front()), vec[i][0].pop();
            ans[1].push_back(vec[i][1].front()), vec[i][1].pop();
        }
    }
    if (a[0])
    {
        for (int i = 1; i <= 26; i++)
        {
            while (b[i] && a[0])
            {
                --a[0], --b[i];
                ans[0].push_back(vec[0][0].front()), vec[0][0].pop();
                ans[1].push_back(vec[i][1].front()), vec[i][1].pop();
            }
        }
    }
    if (b[0])
    {
        for (int i = 1; i <= 26; i++)
        {
            while (b[0] && a[i])
            {
                --a[i], --b[0];
                ans[0].push_back(vec[i][0].front()), vec[i][0].pop();
                ans[1].push_back(vec[0][1].front()), vec[0][1].pop();
            }
        }
    }
    while (a[0] && b[0])
    {
        --a[0], --b[0];
        ans[0].push_back(vec[0][0].front()), vec[0][0].pop();
        ans[1].push_back(vec[0][1].front()), vec[0][1].pop();
    }
    int size = (ans[0].size() + ans[1].size()) / 2;
    printf("%d\n", size);
    for (int i = 0; i < size; i++)
        printf("%d %d\n", ans[0][i], ans[1][i]);
    return 0;
}
```

---

## 作者：Pretharp (赞：0)

### 1、思路实现

这道题本身并不难，你只要掌握了基础的 $C++$ 语法就可以切掉这道大模拟题，但是有很多是需要我们注意的细节。

首先，暴力枚举两个匹配的字符是肯定不行，所以我们可以使用 $a$ 数组和 $b$ 数组记录两个字符串中，每个字符的数量。同时，我们可以定义两个队列数组来储存每个字母的位置，再定义两个队列数组来储存答案。

接下来，我们要考虑怎么匹配两个字符。

1. 首先，$"?"$ 是可以匹配任意的字符，因此，我们要尽可能的用 $"?"$ 来匹配无法与其它字母来匹配的字母。所以第一步，我们用字母匹配字母。

1. 剩下的都是只能与 $"?"$ 匹配的字母了，所以我们用 $"?"$ 来匹配其它的字母。

1. 如果字母匹配完了，剩下的只有 $"?"$ 了，这时我们用 $"?"$ 来匹配 $"?"$ 。

### 2、代码实现

具体细节不多说，看代码注释。

```cpp
#include<bits/stdc++.h>
#define int long long
#define QWQ while(1) cout<<"yee"
using namespace std;
const int N=30;
int a[N],b[N],n,idx;
queue<int> ans1,ans2;
queue<int> aw[N],bw[N];
// 数组 a 和 b 用于记录字符串中每种字符的数量，下标 0 用于记录问号。 
// 队列数组 aw 和 bw 用于记录每个字符的位置，下标 0 用于记录问号。 
// ans1 和 ans2 用于记录答案。
// n 是长度， idx 是能匹配的字符数量。 
char x;
signed main()
{
	QWQ; // QWQ
	cin>>n;
	// 一边输入一边处理。 
	for(int i=1;i<=n;i++){
		cin>>x; 
		if(x=='?'){
			a[0]++;
			aw[0].push(i);
		}else{
			a[x-'a'+1]++;
			aw[x-'a'+1].push(i);
			// push(i) 就是记录位置。 
			// 这里类似于离散化，下标 0 记录问号。 
		}
	}
	// 与上面的循环相同。 
	for(int i=1;i<=n;i++){
		cin>>x;
		if(x=='?'){
			b[0]++;
			bw[0].push(i);
		}else{
			b[x-'a'+1]++;
			bw[x-'a'+1].push(i);
		}
	}
	// 匹配字母与字母。 
	for(int i=1;i<=26;i++){
		// 枚举每个字母，如果当前两个字符串都还拥有这个字母，就循环。 
		while(a[i] && b[i]){
			a[i]--,b[i]--; // 字母数量减一。 
			ans1.push(aw[i].front());
			aw[i].pop();
			// 记录答案，同时被使用的字母出队。 
			ans2.push(bw[i].front());
			bw[i].pop();
			// 同上。 
			idx++; // 答案加一。 
		}
	}
	// 用问号匹配字母。 
	for(int i=1;i<=26;i++){
		while(b[i] && a[0]){
			a[0]--,b[i]--;
			ans1.push(aw[0].front());
			aw[0].pop();
			ans2.push(bw[i].front());
			bw[i].pop();
			// 与之前的字母匹配字母类似。 
			idx++;
		}
	}
	// 与上面的循环一样。 
	for(int i=1;i<=26;i++){
		while(a[i] && b[0]){
			a[i]--,b[0]--;
			ans1.push(aw[i].front());
			aw[i].pop();
			ans2.push(bw[0].front());
			bw[0].pop();
			idx++;
		}
		
	}
	// 问号匹配问号。 
	while(a[0] && b[0]){
		a[0]--,b[0]--;
		ans1.push(aw[0].front());
		aw[0].pop();
		ans2.push(bw[0].front());
		bw[0].pop();
		idx++;
	}
	cout<<idx<<endl;
	for(int i=1;i<=idx;i++){
		cout<<ans1.front()<<" "<<ans2.front()<<endl;
		ans1.pop();
		ans2.pop();
	}
	// 输出，完美的结束。 
    return 0;
}
```

---

## 作者：zhy12138 (赞：0)

本文同步发表于[我的博客](https://zhy12138.github.io/2019/03/24/CF-1141-div3/)

感觉这题还简单些

读入两个字符串后，分别将不同的小写字母的位置和`?`的位置压入不同的数组中

然后暴力比较弹数就行了（注意比较顺序）

注：这题用`vector`、`queue`或者像我一样用数组都行
```cpp
#include<iostream>/**/
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<ctime>
#define ll long long
using namespace std;
inline int read()
{
    int kkk=0,x=1;
    char c=getchar();
    while((c<'0' || c>'9') && c!='-')
        c=getchar();
    if(c=='-')
        c=getchar(),x=-1;
    while(c>='0' && c<='9')
        kkk=(kkk<<3)+(kkk<<1)+(c-'0'),c=getchar();
    return kkk*x;
}
int num_l[26][150001],num_r[26][150001],lq,rq,n,l[150001],r[150001],ans[150001][2],maxn;
char s1[150001],s2[150001];
int main()
{
	n=read();
	cin>>s1>>s2;
	for(register int i=0;i<n;++i)
		if(s1[i]=='?')
			l[++lq]=i+1;
		else
		{
			int c=s1[i]-'a';
			num_l[c][++num_l[c][0]]=i+1;
		}
	for(register int i=0;i<n;++i)
		if(s2[i]=='?')
			r[++rq]=i+1;
		else
		{
			int c=s2[i]-'a';
			num_r[c][++num_r[c][0]]=i+1;
		}
	for(register int i=0;i<26;++i)
		while(num_l[i][0] && num_r[i][0])
		{
			ans[++maxn][0]=num_l[i][num_l[i][0]];
			ans[maxn][1]=num_r[i][num_r[i][0]];
			--num_l[i][0];
			--num_r[i][0];
		}
	for(register int i=0;i<26;++i)
		while(num_l[i][0] && rq)
		{
			ans[++maxn][0]=num_l[i][num_l[i][0]];
			ans[maxn][1]=r[rq];
			--rq;
			--num_l[i][0];
		}
	for(register int i=0;i<26;++i)
		while(num_r[i][0] && lq)
		{
			ans[++maxn][0]=l[lq];
			ans[maxn][1]=num_r[i][num_r[i][0]];
			--lq;
			--num_r[i][0];
		}
	while(lq && rq)
	{
		ans[++maxn][0]=l[lq];
		ans[maxn][1]=r[rq];
		--lq;
		--rq;
	}
	printf("%d\n",maxn);
	for(register int i=1;i<=maxn;++i)
		printf("%d %d\n",ans[i][0],ans[i][1]);
    return 0;
}
```

---

## 作者：da32s1da (赞：0)

考虑统计每个字母的出现次数，然后相同字母优先匹配，问号再和字母匹配，最后问号和问号匹配。

```cpp
#include<cstdio>
#include<queue>
using namespace std;
const int N=15e4+50;
typedef pair<int,int> pr;
int n,cnt;
char s[N],t[N];
queue<int>vp1[30],vp2[30];
pr a[N];
int main(){
    scanf("%d%s%s",&n,s,t);
    for(int i=0;i<n;i++)
    if(s[i]!='?')vp1[s[i]-96].push(i+1);
    else vp1[0].push(i+1);
    for(int i=0;i<n;i++)
    if(t[i]!='?')vp2[t[i]-96].push(i+1);
    else vp2[0].push(i+1);
    //统计字母出现次数
    for(int i=1;i<=26;i++){
        int j=min(vp1[i].size(),vp2[i].size());
        for(int k=0;k<j;k++){
            a[++cnt]=pr(vp1[i].front(),vp2[i].front());
            vp1[i].pop();vp2[i].pop();
        }
    }
    //字母优先匹配
    for(int i=1;i<=26;i++){
        int j=min(vp1[0].size(),vp2[i].size());
        for(int k=0;k<j;k++){
            a[++cnt]=pr(vp1[0].front(),vp2[i].front());
            vp1[0].pop();vp2[i].pop();
        }
    }
    //A的?和B的字母匹配
    for(int i=1;i<=26;i++){
        int j=min(vp1[i].size(),vp2[0].size());
        for(int k=0;k<j;k++){
            a[++cnt]=pr(vp1[i].front(),vp2[0].front());
            vp1[i].pop();vp2[0].pop();
        }
    }
    //A的字母和B的?匹配
    int j=min(vp1[0].size(),vp2[0].size());
    for(int k=0;k<j;k++){
        a[++cnt]=pr(vp1[0].front(),vp2[0].front());
        vp1[0].pop();vp2[0].pop();
    }
    //?互相匹配
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++)printf("%d %d\n",a[i].first,a[i].second);
}
```

---


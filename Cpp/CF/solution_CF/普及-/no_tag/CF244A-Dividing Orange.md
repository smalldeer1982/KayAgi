# Dividing Orange

## 题目描述

有一个橙子，分成 $n⋅k$ 瓣，编号为 $1,2,3,\cdots n\cdot k$。现在要分给 $k$ 个小孩，以下是给橙子的规则：
- 每个小孩得到 $n$ 瓣橙子。
- 第 $i$ 个小孩有一个对橙子的要求：$a_i$，即他得到的橙子瓣中必须有编号为 $a_i$ 的橙子瓣。

保证没有两个小孩的 $a_i$ 相同。

## 样例 #1

### 输入

```
2 2
4 1
```

### 输出

```
2 4 
1 3 
```

## 样例 #2

### 输入

```
3 1
2
```

### 输出

```
3 2 1 
```

# 题解

## 作者：卷王 (赞：8)

前言：这题很水，只能评红。代码也很短。之前分析的不是很好，现在改了，感谢大家指出错误。

这题给出 $n×k$ 个橙子，有 $n$ 个人，每个人都能得到 $n$ 个橙子，但是第 $i$ 个小孩想要得到第 $a_i$ 个橙子（瓣），请输出任意一种可行的方案。

这题的主要思路是用[bitset](https://www.cnblogs.com/magisk/p/8809922.html)，注意需要加头文件<bitset>，其实只需要先处理有要求的 $k$ 个人，其次再处理其他还没被用过的橙子，就这么简单~~

下面放AC代码： 

```cpp
//请勿抄袭，共建美好洛谷！
//made in china 

#include<cstdio>
#include<bitset>
using namespace std;
bitset<1001>ds; //STL大法好！ 
int a[50],cnt=1,n,k;
inline int read();
int main()
{
	n=read(),k=read();
	for(int i=1;i<=k;i++)
	{
		a[i]=read();
		ds[a[i]]=1;
	}
	for(int i=1;i<=k;i++)
	{
		printf("%d ",a[i]);
		tmp=n-1;
		while(tmp--)
		{
			while(ds[cnt]) cnt++;
			printf("%d ",cnt);
			l++;
		}
		printf("\n");
	}
	return 0;
}
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
```

---

## 作者：krjt (赞：7)

前言：[BITSET](https://oi-wiki.org/lang/csl/bitset/)

题目大意： $n\times k$ 个东西，每个人 $n$ 个东西，并且第 $i$ 个人要得到 $a_i$ 个东西，现求分配方案。

思路：先去存有要求的（即第 $i$ 个人要第 $a_i$ 橙子）然后其他橙子就可以随便分啦！！

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bitset<1001>u;
int a[50],l=1,n,k;
int main(){
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		cin>>a[i];
		u[a[i]]=1;
	}
	for(int i=1;i<=k;i++){
		cout<<a[i]<<" ";
		int j=n-1;
		while(j--){
			while(u[l]){
			    l++;
			}
			cout<<" "<<l++;
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：123456zmy (赞：3)

题意：  
你要把 $n\times k$ 个数分给 $k$ 个人，每个人 $n$ 个数，并且第 $i$ 给人要求得到 $a_i$，输出任意一个分配方案（保证有解）。
___
用一个数组记录哪些是被要求的，然后记录选到第几个，每次输出要求的和后面没被要的。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bitset<1001>u;
int a[31],i1=1,n,k;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&a[i]);
		u[a[i]]=1;
	}
	for(int i=1;i<=k;i++)
	{
		printf("%d ",a[i]);//要的
		int j=n;
		while(--j)
		{
			while(u[i1])++i1;//找到没人要的
			printf("%d ",i1++);//防止重复输出
		}
		putchar(10);//换行
	}
	return 0;
}
```

---

## 作者：zzy_zzy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF244A)
### 题目大意
现有 $n\times{}k$ 个物品给 $k$ 个人平均分，且要求第 $i$ 个人要拥有第 $a_i$ 个物品，输出一种分配方案。
### 思路
可以先把每个人必须得到的先给他，剩下的就随便分配。

**AC code:**
```cpp
#include<bits/stdc++.h>
using namespace std;
int have[910];
/*
have[1],have[1+k],have[1+2k]...为第一个人所得到的，
have[2],have[2+k],have[2+2k]...为第二个人所得到的，以此类推。
*/
bool is_have[910];  //判断一件物品是否被某人所拥有
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=k;i++){
        cin>>have[i];
        is_have[have[i]]=1;    //必须分配的先分配
    }
    int tot=k;
    for(int i=1;i<=n*k;i++){
        if(is_have[i]==0){
            have[++tot]=i;
            is_have[i]=1;   //剩下的随意分配
        }
    }
    for(int i=1;i<=k;i++){
        for(int j=1;j<=n;j++){
            cout<<have[i+k*(j-1)]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```
代码时间复杂度为 $O(nk)$，不会超时。

---

## 作者：KK_lang (赞：1)

## 思路

首先，每个人有一个自己想要的 $a_i$，又 $a_i$ 不重复，所以每个人肯定有一个自己想要的。

那么剩下的就没要求了，要求输出一种可能，就遍历每瓣橘子，只要没被“预定”或者被前面的人拿，就拿走。

## AC Code

具体的思路和代码实现，看程序注释。

```cpp
#include<iostream>
using namespace std;

int n, k;
int a[40]; // 每个人想要的
bool orange[1010], is_want[1010];
// orange[i] 表示第i个橘子有没有被拿；is_want[i] 表示这个橘子是不是某人想要的
// 由于每次判断这瓣有没有人预定很麻烦，所以可以写一个 bool 桶，判断这个是不是被“预定的”，存在 is_want

int main()
{
    cin >> n >> k;
    for(int i = 1; i <= k; i++)
    {
        cin >> a[i];
        is_want[a[i]] = 1; // 这一个是有人想要的
    }
    // 每个人有自己想要的，接下来就随便取能取的就行了
    for (int i = 1; i <= k; i++)
    {
        orange[a[i]] = 1; // 想要的就一定拿，保证 is_want 和 orange 同步
        cout << a[i] << ' '; // 拿了它，输出
        int cnt = 1; // 记录当前人拿了多少个，已经拿了一个 a[i] 了，所以初值为 1
        for (int j = 1; j <= n * k;j++)
        {
            if (!is_want[j] && !orange[j]) // 只要不是别人“预定”的或者别人拿过的，就拿
            {
                cnt++, orange[j] = 1; // 多拿了一个，这个被拿了
                cout << j << " "; // 拿了它，输出
            }
            if (cnt == n) break; // 拿了 n 个了，不用再拿了
        }
        cout << endl; // 要换行
    }
    return 0;
}
```
时间复杂度 $O(k \times n^2)$，相当于三次方做法，范围 $1 \leq n, k \leq 30$，时间复杂度完全可以过。

红题水平，祝大家都能 AC！

---

## 作者：Night_sea_64 (赞：1)

此题是个超级无敌大水题。

我们先把每个人要的那个 $a_i$ 给他们，然后其它的随便分就好了因为他是 spj。

具体思路见代码：

```cpp
#include<iostream>
using namespace std;
int a[40];
bool flag[1010];//flag 记录这个有没有用过。
bool f[1010];//f 记录这个是不是某一个人想要的。
int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=k;i++)
    {
        cin>>a[i];
        f[a[i]]=1;
    }
    for(int i=1;i<=k;i++)
    {
        flag[a[i]]=1;
        cout<<a[i]<<' ';
        //先把这个人要的那个给他。
        int cnt=1;//初值设 1，因为已经给一个了。
        //暴力枚举给这个人的是哪些。
        for(int j=1;j<=n*k;j++)
        {
            if(!f[j]&&!flag[j])//如果没有用过并且不是某一个人想要的就给他。
            {
                cnt++,flag[j]=1;
                cout<<j<<" ";
            }
            if(cnt==n)break;//给够 n 个了就退出。
        }
        cout<<endl;
    }
    return 0;
}
```

---


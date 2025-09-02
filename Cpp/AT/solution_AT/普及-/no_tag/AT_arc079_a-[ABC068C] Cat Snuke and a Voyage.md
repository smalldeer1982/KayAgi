# [ABC068C] Cat Snuke and a Voyage

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc068/tasks/arc079_a

高橋キングダムには、高橋諸島という、$ N $ 個の島からなる諸島があります。 便宜上、これらの島を島 $ 1 $、島 $ 2 $、 ...、島 $ N $ と呼ぶことにします。

これらの諸島の間では、船の定期便が $ M $ 種類運行されています。 定期便はそれぞれ $ 2 $ つの島の間を行き来しており、$ i $ 種類目の定期便を使うと、 島 $ a_i $ と島 $ b_i $ の間を行き来する事ができます。

すぬけくんは今島 $ 1 $ にいて、島 $ N $ に行きたいと思っています。 しかし、島 $ 1 $ から島 $ N $ への定期便は存在しないことがわかりました。 なので、定期便を $ 2 $ つ使うことで、島 $ N $ に行けるか調べたいと思っています。

これを代わりに調べてあげてください。

## 说明/提示

### 制約

- $ 3\ ≦\ N\ ≦\ 200,000 $
- $ 1\ ≦\ M\ ≦\ 200,000 $
- $ 1\ ≦\ a_i\ <\ b_i\ ≦\ N $
- $ (a_i,\ b_i)\ \neq\ (1,\ N) $
- $ i\ \neq\ j $ ならば $ (a_i,\ b_i)\ \neq\ (a_j,\ b_j) $

### Sample Explanation 2

島 $ 4 $ へ行くには、定期便を $ 3 $ つ使う必要があります。

### Sample Explanation 4

島 $ 1 $、島 $ 4 $、島 $ 5 $ と移動すれば $ 2 $ つの定期便で移動可能です。

## 样例 #1

### 输入

```
3 2
1 2
2 3```

### 输出

```
POSSIBLE```

## 样例 #2

### 输入

```
4 3
1 2
2 3
3 4```

### 输出

```
IMPOSSIBLE```

## 样例 #3

### 输入

```
100000 1
1 99999```

### 输出

```
IMPOSSIBLE```

## 样例 #4

### 输入

```
5 5
1 3
4 5
2 3
2 4
1 4```

### 输出

```
POSSIBLE```

# 题解

## 作者：zybnxy (赞：4)

一开始没有思路，~~一定是我太弱了~~直到翻开题解才恍然大悟~~就是太弱了~~

其实本来想跑一遍最短路~~然而看到数据果断放弃~~。

#### 正解 ：题意说只能坐两次船，那么肯定第一次从起点出发，第二次在终点结束
所以我们可以开两个数组A和B，$A_i$用来放置第一次坐船后的终点，$B_i$用来放置第二次坐船的起点，如果有$A_i$==1且$B_i$==1，则肯定可以到达。

以下是我简洁~~丑陋~~的代码

时间复杂度 $O(N)$

```cpp
#include<cstdio>
int a[1000001],b[1000001];
int main()
{
	int n,m,i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		int st,ed;
		scanf("%d%d",&st,&ed);
		if(st==1)a[ed]=1;//记录第一次坐船的终点 
		if(ed==n)b[st]=1;//记录第二次坐船的起点 
	}
	for(i=1;i<=m;i++)
		if(a[i]&&b[i])//等价于a[i]==1&&b[1]==1 
		{
			printf("POSSIBLE\n");return 0;//若有，直接退出 
		}
	printf("IMPOSSIBLE\n");
	return 0;
}


```

---

## 作者：loceaner (赞：2)

#### 这是一道划船问题，因为只问两次能不能到达，从1道n只能转一次船也必须转一次船，所以需要有【1，c】，【c，n】两条船，所以只需要保存a=1的值和b=n的值就可以了。

代码相比楼上略长，在这里orz一下啦

```cpp
#include<bits/stdc++.h>
#define N 200010
using namespace std;

int arr[N];
int brr[N];
int p=0,q=0;
int n,m；

int main() {
	cin>>n>>m;
	for(int i=0; i<m; i++) {
		int a,b；
		cin>>a>>b;
		if(a==1) arr[p++]=b;
		if(b==n) brr[q++]=a;
	}
	if(p==0||q==0) {
		cout<<"IMPOSSIBLE";
		return 0;
	}
	sort(arr,arr+p);
	sort(brr,brr+q);
	int i,j=1;
	for(i=0; i<p; i++) {
		j--;
		for(j; j<q; j++) {
			if(arr[i]==brr[j]) {
				break;
			}
			if(arr[i]<brr[j])
				break;
		}
		if(arr[i]==brr[j])
			break;
	}
	if(arr[i]==brr[j]&&i!=p)
		cout<<"POSSIBLE";
	else
		cout<<"IMPOSSIBLE";
	return 0;
}
```
已做防作弊处理，一定要自觉哦！



---

## 作者：智子·起源 (赞：0)

### 这又是另一种思维方向。

排除掉一步到位的方法之外，剩下的就是在中间停留有一个岛的了。


那我们就可以在输入的时候记录一下，当前路线可不可以从中间的任意一个岛到达起点（1）或终点（n）。如果可以，就把该路线中中间岛的位置存入一个数组。

最后，再把存位置的数组排序，找出任意一对相同的数那就证明是可以两步完成的。

因为对于中间的某一个岛，它有两条路通向起点或终点，那必定是一个起点，一个终点。

就是这种既神奇又简单的方法。

看大家都没用，就来水一发qwq

其原理可以由下图展示。

![](https://cdn.luogu.com.cn/upload/image_hosting/upi7po0q.png)

接下来，上代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int n,m,a[2000000+5],a_n,x,y; 
int main()
{
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++)
  {
    scanf("%d%d",&x,&y);
    if(x==1)
    {
      if(y==n){printf("POSSIBLE\n");return 0;}
      a_n++,a[a_n]=y;
    }
    if(x==n)
    {
      if(y==1){printf("POSSIBLE\n");return 0;}
      a_n++,a[a_n]=y;
    }
    if(y==1)
    {
      if(x==n){printf("POSSIBLE\n");return 0;}
      a_n++,a[a_n]=x;
    }
    if(y==n)
    {
      if(x==1){printf("POSSIBLE\n");return 0;}
      a_n++,a[a_n]=x;
    }
  } 
  sort(a+1,a+1+a_n);
  for(int i=1;i<=a_n;i++)
    if(a[i]==a[i+1]){printf("POSSIBLE\n");return 0;}
  printf("IMPOSSIBLE\n");
  return 0;
}

```


---


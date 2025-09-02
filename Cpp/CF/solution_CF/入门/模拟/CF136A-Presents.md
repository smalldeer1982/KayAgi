# Presents

## 题目描述

小 Petya 非常喜欢礼物。最近，他收到了妈妈送的新年礼物——一台新笔记本电脑。他立刻决定把它送给别人，因为还有什么比送别人礼物更让人开心的呢？于是，他在家里举办了一场新年派对，并邀请了 $n$ 个朋友。

如果说 Petya 有什么比收礼物更喜欢的事情，那就是看别人互相送礼物。因此，他把笔记本电脑安全地藏起来，等到下一个新年再拿出来，并决定只观看朋友们互相交换礼物，自己不参与。他用 $1$ 到 $n$ 的整数给所有朋友编号。Petya 记得编号为 $i$ 的朋友把礼物送给了编号为 $p_i$ 的朋友。他还记得每个朋友都恰好收到了一份礼物。

现在，Petya 想知道，对于每个朋友 $i$，是谁把礼物送给了他。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
2 3 4 1
```

### 输出

```
4 1 2 3
```

## 样例 #2

### 输入

```
3
1 3 2
```

### 输出

```
1 3 2
```

## 样例 #3

### 输入

```
2
1 2
```

### 输出

```
1 2
```

# 题解

## 作者：Wei_ch (赞：2)

根据题意，我们可以定义一个数组用来记录，来记录**第下标个人**收到了来自谁的礼物。在输入的时候就把数存进数组里，再循环输出。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105],t;
int main(){
	cin>>n;
    for(int i=1;i<=n;i++)	cin>>t,a[t]=i;//存进数组里
	for(int j=1;j<=n;j++)	cout<<a[j]<<" "; //循环输出
}
```

---

## 作者：liJason (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF136A)

~~一道很水的红题~~

## 题目大意
题意已经很简明了，就不解释了。

我们需要一个数组 $a$，$a_i$ 表示第 $i$ 个人给第几个人送了礼物。再要一个数组 $b$，$b_i$ 表示第 $i$ 个人被第几个人送了礼。因此对于第 $i$ 个人，都有 $b_{a_i}=i$。

## 下面上代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],b[105];

int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		cout<<b[i]<<" ";
	}
	return 0;
}
```

---

## 作者：Mark0104 (赞：0)

这题是一道水题，意思翻译已经讲的很清楚了，就不解释了，我们可以定义一个 $ans$ 数组，在输入的时候预处理结果。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,ans[101];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		ans[a]=i;//预处理 
	}
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i]<<" ";//输出结果 
	}
	return 0;
}
```

---

## 作者：hensier (赞：0)

~~这道题居然有$101$个测试点。~~

该题其实就是新建两个数组然后进行挨个处理。其实跟桶的算法差不多。

代码：
```cpp
#include<cstdio>
int n,i,a[101],b[101];
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)scanf("%d",&a[i]),b[a[i]]=i;//这里的意思就是把a[i]（即把i存入b桶中，序号为a[i]，表示i送礼物给a[i]）
    for(i=1;i<=n;i++)printf("%d ",b[i]);//输出
}
```

---

## 作者：小鲍bob (赞：0)

### 此题主要是模拟，思维方面训练不是太强
首先我们分析一下题目：大意是有n个人，互相送礼物，输入的是几就是送给第几个人。
分析一下样例：

| 4 |  |  |  |
| -----------: | -----------: | -----------: | -----------: |
| 2 | 3 |  4| 1 |

第一个人给第二个人送了礼物，在第二个那里就输出1，以此类推。

分析过题目后，我们就可以开始做了：
本题我采用的是时间复杂度为O(n)的方法，主要就是输入时将它们放入数组里

本题有两种方法：

1)代码如下：

```
#include<iostream>
using namespace std;
int main()
{
	int n,i,x,a[100]={0};
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>x;
		a[x]=i;
	}
	for(i=1;i<=n;i++)
	{
		cout<<a[i]<<' ';
	}
	return 0;
 } 
```
这种方法是传统的暴力，但是我们可以输入时只输入(n-1)个数，这样时间省一点。

2)最后代码如下：
```
#include<iostream>
using namespace std;
int main()
{
	int n,i,x,a[100]={0};
	cin>>n;
	for(i=1;i<=n-1;i++)
	{
		cin>>x;
		a[x]=i;
	}
	for(i=1;i<=n;i++)
	{
		if(a[i]==0) cout<<n<<' ';
		else cout<<a[i]<<' ';
	}
	return 0;
 } 
```
第二种方法，比第一种方法时间省了0.04s。只有多思考优化，才能没有那么容易超时。

---

## 作者：flying_cheng (赞：0)

这题楼上的dalao都用模拟做的，但其实可以用桶排思想去做，时间只有O(n)，详见代码：
```c
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b[101],d[101]={};
	cin>>a;
	for(int c=0;c<a;c++)
	{
		cin>>b[c];
		d[b[c]-1]=c+1;//核心代码，在另一个数组将
        			下标与数值互换，使得送礼
                    		物的人变成数值，送礼物的
                            	对象变成下标。
	}
	for(int c=0;c<a;c++)
	{
		cout<<d[c]<<" ";//按顺序输出就可以了
	}
	return 0;
}

```
码风不好，请谅解QwQ

------------
# 拒绝抄袭从我做起


---

## 作者：yuangq (赞：0)

蒟蒻用了一个 $N^2$ 的方法 但因为数据太小还是能过。详情请看注释

~~~
#include<bits/stdc++.h>
using namespace std;
int n;
int a[105];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];//输入 
	}
	for(int i=1;i<=n;i++)
	{
		//查找第i个人礼物的送礼者 
		for(int j=1;j<=n;j++)
		{
			if(a[j]==i)
			{
				cout<<j<<" ";//找到了 
			} 
		}
	}
	return 0;
}
~~~

---

## 作者：OdtreePrince (赞：0)

# — 模拟 — 
$\color{blue}\texttt{模拟出奇迹，看不懂题目的看代码。}$
--
题目看懂了真的没什么
--
输入

4

2 3 4 1

样例意为 1给了2 礼物，2给了3礼物，3给了4礼物，4给了1礼物

输出

4 1 2 3

样例意为 1的礼物是4给的，2的礼物是1给的，3的礼物是2给的，4的礼物是3给的。输出 4 1 2 3。

本蒟蒻用give数组存储 i给give[i]。

$\color{orange}\texttt{多说无益，上代码。}$
~~~#include<bits/stdc++.h>
using namespace std;
int give[100005];
int main(){
    int n,k;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>k;
        give[k]=i;
    }
    for(int i=1;i<=n;i++){
        cout<<give[i]<<' ';
    }
    return 0;
}~~~


---


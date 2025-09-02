# Rudolph and Mimic

## 题目描述

This is an interactive task.

Rudolph is a scientist who studies alien life forms. There is a room in front of Rudolph with $ n $ different objects scattered around. Among the objects there is exactly one amazing creature — a mimic that can turn into any object. He has already disguised himself in this room and Rudolph needs to find him by experiment.

The experiment takes place in several stages. At each stage, the following happens:

- Rudolf looks at all the objects in the room and writes down their types. The type of each object is indicated by a number; there can be several objects of the same type.
- After inspecting, Rudolph can point to an object that he thinks is a mimic. After that, the experiment ends. Rudolph only has one try, so if he is unsure of the mimic's position, he does the next step instead.
- Rudolf can remove any number of objects from the room (possibly zero). Then Rudolf leaves the room and at this time all objects, including the mimic, are mixed with each other, their order is changed, and the mimic can transform into any other object (even one that is not in the room).
- After this, Rudolf returns to the room and repeats the stage. The mimic may not change appearance, but it can not remain a same object for more than two stages in a row.

Rudolf's task is to detect mimic in no more than five stages.

## 说明/提示

Explanation for the first test: initial array is $ x_1 $ , $ x_2 $ , $ x_3 $ , $ x_4 $ , $ x_5 $ . Mimic is in first position.

- Delete the fifth object. After that, the positions are shuffled, and the mimic chose not to change his appearance. Object positions become $ x_4 $ , $ x_1 $ , $ x_2 $ , $ x_3 $ .
- Delete the third objects. The mimic is forced to turn into another object, because it has already been in the form $ 1 $ for two stages. The mimic chose to transform into $ 2 $ , the objects are shuffled and become $ x_3 $ , $ x_4 $ , $ x_1 $ .
- Delete the first and second objects. The objects positions become $ x_1 $ . Only the mimic remains, and it remains an object $ 2 $ .
- Point to the first element.

## 样例 #1

### 输入

```
3
5
1 1 2 2 3

2 1 1 2

2 2 2

2

8
1 2 3 4 3 4 2 1

4 3 4 3 2 2 1 3
 
2 3 3 2

5 3 2

2 5

15
1 2 3 4 5 6 7 8 7 6 5 4 3 2 1 

1 2 3 4 5 6 7 8 7 9 5 4 3 2 1```

### 输出

```
- 1 5

- 1 3

- 2 1 2

! 1


- 0

- 4 1 3 7 8

- 1 4

- 1 2

! 2


- 0

! 10```

# 题解

## 作者：Coffee_zzz (赞：7)

不如说是脑筋急转弯题。

### 分析

题目中有一个关键信息：

> The mimic may not change appearance, but it can not remain a same object for more than two stages in a row.

也就是说模仿者最多隔 $2$ 轮就会变一次形态。

那我们先一直输出 `- 0`，直到它变换形态，这时最少还剩 $3$ 次操作机会。

它变换形态后，变成的那种物体数量会增加 $1$。我们把其他物体都拿走，就留下数量增加 $1$ 的这种物体。这时最少还剩 $2$ 次操作机会。

接下来我们再一直输出 `- 0`，直到它变化形态。变化形态后，本来全部相同的物体，会变成若干个相同的物体和一个不同的物体，那个不同的物体就是模仿者了。这里最多消耗 $2$ 次操作机会，最劣情况也不会出现问题。

```c++
int a[205],sum[10],cnt[10];
void solve(){
	int n,k;
	cin>>n;
	memset(sum,0,sizeof sum);
	for(int i=1;i<=n;i++) cin>>a[i],sum[a[i]]++;
	cout<<"- 0"<<endl;
	fflush(stdout);
	while(1){
		memset(cnt,0,sizeof cnt);
		for(int i=1;i<=n;i++) cin>>a[i],cnt[a[i]]++;
		for(k=1;k<=9;k++) if(cnt[k]==sum[k]+1) break;
		if(k!=10) break;
		cout<<"- 0"<<endl;
		fflush(stdout);
	}
	cout<<"-";
	int m=0;
	for(int i=1;i<=n;i++) if(a[i]!=k) m++;
	cout<<' '<<m;
	for(int i=1;i<=n;i++) if(a[i]!=k) cout<<' '<<i;
	cout<<endl;
	fflush(stdout);
	n=n-m;
	while(1){
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++){
			if(a[i]!=k){
				cout<<"! "<<i<<endl;
				fflush(stdout);
				return;
			}
		}
		cout<<"- 0"<<endl;
		fflush(stdout);
	}
}
```

---

## 作者：紊莫 (赞：2)

有趣交互题。

关键句是：外星生物不能连续两轮都选择不改变状态。那么我们可以一直输出 ``- 0`` 来等待他改变，第一次找出某个种类多了一个，那么就把其他数字都删掉，留下这个种类，再输出 ``- 0`` 直到其再次改变，那么不一样的就是答案，显然操作次数不会超过 $5$ 次。

[示例代码。](https://codeforces.com/contest/1846/submission/240871137)

---

## 作者：_sunkuangzheng_ (赞：1)

**【题目分析】**

我们注意到，每次修改只会有一个数字可能发生改变，且两轮以内一定发生改变。因此先询问 `- 0`，如果没有数字发生改变，就再询问一次，就可以确定这个变了的数字，将无用的数字删掉，剩下的数字都是相等的。这部分代码如下：

```cpp
        cin >> n;bool flag = 0;int tot = 0;
        for(int i = 0;i <= 9;i ++) b[i] = c[i] = 0;
        for(int i = 1;i <= n;i ++) cin >> a[i],b[a[i]] ++;
        cout << "- 0" << endl;cout.flush();
        for(int i = 1;i <= n;i ++) cin >> a[i],c[a[i]] ++;
        for(int i = 1;i <= n;i ++) if(b[a[i]] < c[a[i]]) {k = a[i],flag = 1;break;}
        if(!flag){
            for(int i = 0;i <= 9;i ++) c[i] = 0;
            cout << "- 0" << endl;cout.flush();
            for(int i = 1;i <= n;i ++) cin >> a[i],c[a[i]] ++;
            for(int i = 1;i <= n;i ++) if(b[a[i]] < c[a[i]]) {k = a[i],flag = 1;break;}
        }
        for(int i = 1;i <= n;i ++) if(a[i] != k) tot ++;
        cout << "- " << tot;cout.flush();
        for(int i = 1;i <= n;i ++) if(a[i] != k) cout << " " << i,cout.flush();
        cout << endl;flag = 0;cout.flush();
```

然后我们就把所有数字都变成了一样的。只要再询问两次，就可以找到那个变了的数字，代码如下：

```cpp
        for(int i = 1;i <= n-tot;i ++) cin >> a[i];
        for(int i = 1;i <= n-tot;i ++) if(a[i] != k) {cout << "! " << i << endl;flag = 1;break;}
        cout.flush();
        if(flag) continue;
        cout << "- 0" << endl;
        cout.flush();
        for(int i = 1;i <= n-tot;i ++) cin >> a[i];
        for(int i = 1;i <= n-tot;i ++) if(a[i] != k) {cout << "! " << i << endl;flag = 1;break;}
        cout.flush();
```

感觉这题比 E2 水。

---

## 作者：Exp10re (赞：0)

啊这个翻译好有趣啊。

## 解题思路

注意到 Rudolph 在去除 Mimic 的时候会立刻暴毙，因此我们在开局不能判断 Mimic 的时候不能贸然行动，于是我们两次都不进行操作，这样的话 Mimic 至少会变换一次形态，只需要判断其中的哪个数数量增多了 1 就可以判断 Mimic 变成了什么数。

举例：初始状态如下：

$\color{black}\texttt{1,2,2,2,3,3}$

在此时不能判断 Mimic 的位置。输出 `- 0`。

$\color{black}\texttt{3,1,2,2,2,3}$

在此时仍然不能判断 Mimic 的位置。输出 `- 0`。**注意，数字的顺序可能会改变。**

$\color{black}\texttt{2,2,}\color{red}\texttt{3}\color{black}\texttt{,3,1,3}$

Mimic 被迫变换了它的形态。

我们把数量增加的数记录下来，然后删除其余所有数，因为我们一定能保证其他数全部是安全的。

在例子中，我们删除除了 3 以外的所有数，即执行 `- 3 1 2 4`

$\color{red}\texttt{3}\color{black}\texttt{,3,3}$

如果接下来不能立刻判断 Mimic 的具体位置，那么我们需要再摆烂一回合，这个时候因为距离 Mimic 上一次变换形态已经过去了两回合，所以找到一个不同的数直接指出即可。

$\color{red}\texttt{3}\color{black}\texttt{,3,3}$

因为不能确定 Mimic 的位置，所以选择不行动。输出 `- 0`。

$\color{red}\texttt{2}\color{black}\texttt{,3,3}$

Mimic 再一次被迫变换了形态，此时我们直接指出不同的一位即可。输出 `! 1`。

于是我们就能保证在五次操作内一定能找到 Mimic 了。

## 代码

交互题目记得写 `fflush(stdout)`。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=210;
int n,a[MAXN],cnt[MAXN],ccnt[MAXN],b[MAXN],v;
void work()
{
	int i,j;
	int flag=0;
	memset(cnt,0,sizeof(cnt));
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		cnt[a[i]]++;
	}
	printf("- 0\n");
	fflush(stdout);
	memset(ccnt,0,sizeof(ccnt));
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		ccnt[a[i]]++;
	}
	flag=0;
	for(i=1;i<=9;i++)
	{
		if(ccnt[i]>cnt[i])
		{
			flag=i;
			break;
		}
	}
	if(flag==0)
	{
		printf("- 0\n");
		fflush(stdout);
		memset(ccnt,0,sizeof(ccnt));
		for(i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			ccnt[a[i]]++;
		}
		flag=0;
		for(i=1;i<=9;i++)
		{
			if(ccnt[i]>cnt[i])
			{
				flag=i;
				break;
			}
		}
	}v=0;
	for(i=1;i<=n;i++)
	{
		if(a[i]!=flag)
		{
			b[++v]=i;
		}
	}
	printf("- %d",v);
	for(i=1;i<=v;i++)
	{
		printf(" %d",b[i]);
	}
	printf("\n");
	fflush(stdout);
	n-=v;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=1;i<=n;i++)
	{
		if(a[i]!=flag)
		{
			printf("! %d\n",i);
			fflush(stdout);
			return;
		}
	}
	printf("- 0\n");
	fflush(stdout);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=1;i<=n;i++)
	{
		if(a[i]!=flag)
		{
			printf("! %d\n",i);
			fflush(stdout);
			return;
		}
	}
	return;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		work();
	}
	return 0;
}
```

---


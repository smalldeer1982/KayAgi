# Permutation Game

## 题目描述

 $ n $ children are standing in a circle and playing a game. Children's numbers in clockwise order form a permutation $ a_{1},a_{2},...,a_{n} $ of length $ n $ . It is an integer sequence such that each integer from $ 1 $ to $ n $ appears exactly once in it.

The game consists of $ m $ steps. On each step the current leader with index $ i $ counts out $ a_{i} $ people in clockwise order, starting from the next person. The last one to be pointed at by the leader becomes the new leader.

You are given numbers $ l_{1},l_{2},...,l_{m} $ — indices of leaders in the beginning of each step. Child with number $ l_{1} $ is the first leader in the game.

Write a program which will restore a possible permutation $ a_{1},a_{2},...,a_{n} $ . If there are multiple solutions then print any of them. If there is no solution then print -1.

## 说明/提示

Let's follow leadership in the first example:

- Child $ 2 $ starts.
- Leadership goes from $ 2 $ to $ 2+a_{2}=3 $ .
- Leadership goes from $ 3 $ to $ 3+a_{3}=5 $ . As it's greater than $ 4 $ , it's going in a circle to $ 1 $ .
- Leadership goes from $ 1 $ to $ 1+a_{1}=4 $ .
- Leadership goes from $ 4 $ to $ 4+a_{4}=8 $ . Thus in circle it still remains at $ 4 $ .

## 样例 #1

### 输入

```
4 5
2 3 1 4 4
```

### 输出

```
3 1 2 4 
```

## 样例 #2

### 输入

```
3 3
3 1 2
```

### 输出

```
-1
```

# 题解

## 作者：A_grasser (赞：1)

## 题意简化

给出两个序列，把序列 $l$ 按照特定顺序排进序列 $a$，使得 $a$ 中元素不重复。

## 需要注意的地方

1. 本题应该是 RMJ，本题解只提供一种做法。

## 解法分析

此处表达对翻译的简陋和漏洞百出甚至缺少关键信息表示不满，因为它导致我把这道题拖了半年才做出来。

切入正题，首先我们应用 $l$ 按照生成数据的规律生成一遍 $a$，在过程中如果出现数字重复使用或该位置已有数字且与生成出的数字不同，那就 `-1` 抬走。如果生成成功，就赋值进去，同时标记这个数已经被用了。

之后还会剩一些数还没赋值，这时需要一个一个扫还没用过的数值，给没赋值的 $a_i$ 附上值，如果赋值的过程中没数字可以赋了，也输出 `-1`，直至最终赋完所有值。

上述工作做完，这道题也就迎刃而解了。

最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
int n,m,a[105],l[105];
bool used[105];
int leader(int x){//计算当前赋值的数 
	int q=l[x]-l[x-1];
	if(q<=0) q+=n;//补成正数 
	return q;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		scanf("%d",&l[i]);
	}
	for(int i=2;i<=m;i++){
		if(a[l[i-1]]==0){
			a[l[i-1]]=leader(i);
			if(used[leader(i)]==1){//已经使用过 
				cout<<-1;
				return 0;
			}
			used[leader(i)]=1;
		}
		if(a[l[i-1]]!=leader(i)){//赋值与原有值不相同 
			cout<<-1;
			return 0;
		}
	}
	int now=1;//赋值数值 
	for(int i=1;i<=n;i++){
		if(a[i]==0){
			while(used[now]==1 && now<=n) now++;//找到新的可赋值数 
			if(now>n){
				cout<<-1;
				return 0;
			}
			a[i]=now;
			used[now]=1;//打标记 
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d ",a[i]);
	}
	return 0;
}

```

---

## 作者：小恐 (赞：1)

~~今天貌似洛谷又日爆了~~

~~明明我看到在CF上过了，结果洛谷上还是Waiting。~~

这道题就是给你$l_1$，$l_2$，……$l_m$，让你构造$a_1$，$a_2$，……$a_n$，使得任意的整数$i$（$1\le i < m$）使得$l_i+a_{l_i}\equiv l_{i+1}$($\bmod$ $n$)，且$a_1$，$a_2$，……$a_n$为1~$n$中各一个。若构造不出来，输出$-1$。

~~显然~~，我们只需枚举每相邻的两个$l$，算出他们所对的$a$，如果这个a已经有值又和新算出来的不一样，输出$-1$，或者新算出来的值已经给了另外一个$a$，那么也输出$-1$。然后标记一下这个数已经给过数了，再把这个$a$赋值成这个数。算完以后可能有$a$没被赋值，那就从剩下的随机挑一个就行了。

~~听得云里雾里？~~ 那就上代码吧：
```cpp
#include<stdio.h>
using namespace std;
bool book[105];//标记每个数有没有给过a 
int a[105];//记录答案 
int main()
{
	int last,x;
	int n,m;
	int l;
	scanf("%d%d",&n,&m);
	scanf("%d",&last);//记录上一个数 
	for(int i=1;i<m;++i)
	{
		scanf("%d",&l);//目前的数 
		x=l-last+n;
		x%=n;
		if(x==0)
			x=n;//算出新a的值 
		if(a[last]!=0)//如果这个a被赋过值 
		{
			if(x!=a[last])//如果与原来不同 
			{
				printf("-1");
				return 0;
			}
		}
		else
		{
			if(book[x])//如果给过别的a 
			{
				printf("-1");
				return 0;
			}
			book[x]=1;//标记已经给过a了 
			a[last]=x;//把它给a 
		}
		last=l;//上一个变成现在的啦 
	}
	int now=1;//现在没有找过的最小值 
	for(int i=1;i<=n;++i)
	{
		if(a[i]!=0)//如果给过值 
			printf("%d ",a[i]);
		else
		{
			for(int j=now;j<=n;++j)//从现在没有找过的最小值开始找 
			{
				if(!book[j])//找到了 
				{
					printf("%d ",j);
					now=j+1;//更新 
					break;
				}
			}
		}
	}
	return 0;
}
```
所有的代码都要自己敲，不要Ctrl c+Ctrl v！

---

## 作者：Keroshi (赞：0)

# 题意
有序列 $a_1,a_2,...,a_n$ 和 $l_1,l_2,...,l_m$，给出序列 $l$。      
已知，对于 $1\le i<m$，$a_{l_i}=(l_{i+1}-l_i+n-1) \bmod n +1$。   
对于 $1\le i\le n$，$1 \le a_i \le n$。$a$ 的元素不重复。   
找到符合条件的 $a$。
# 解题思路
首先可以通过序列 $l$ 来求出序列 $a$ 中部分的数。    
那么本题的难点就是判断序列是否合法以及如何构建合法序列。    
可以使用数组 $b$ 来记录已经用过的数，保证元素不重复。   
将 $l$ 遍历完后 $a$ 可能有空的元素，那么就把没用过的元素填进去。   
时间复杂度 $O(n+m)$。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e2+5;
int n,m,a[N],b[N],l[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n >> m;
    for(int i=1;i<=m;i++) cin >> l[i];
    for(int i=2;i<=m;i++){
        int d = l[i] - l[i-1];
        if(d <= 0) d+=n;
        if(!a[l[i-1]]){ // 没有被填过
            a[l[i-1]] = d;
            if(b[d]){ // 有重复元素
                cout << -1 ;
                return 0;
            }
            b[d] = 1;
        } 
        if(a[l[i-1]] != d) { // 与之前填的数冲突
            cout << -1 ;
            return 0;
        }
    }
    int pos=1;
    for(int i=1;i<=n;i++){
        if(!a[i]){ // 没填数的情况
            while(b[pos]&&pos<=n) pos++; // 找没用过的数
            if(pos > n){ // 数用完了
                cout << -1 ;
                return 0;
            }
            a[i] = pos;
            pos++;
        }
    }
    for(int i=1;i<=n;i++) cout << a[i] << " ";
    return 0;
}
```

---


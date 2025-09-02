# [GCJ 2021 Qualification] Reversort

## 题目描述

**注意：问题 "Reversort" 和 "Reversort Engineering" 的题目描述主体部分相同，仅最后一段不同。这两个问题可以独立解决。**

Reversort 是一种用于将**互不相同**的整数列表按升序排序的算法。该算法基于 "Reverse" 操作，每次应用该操作会反转列表中某个连续部分的顺序。

算法的伪代码如下：

```
Reversort(L):
  for i := 1 to length(L) - 1
    j := position with the minimum value in L between i and length(L), inclusive
    Reverse(L[i..j])
```

经过 $i-1$ 次迭代后，列表的第 $1, 2, \ldots, i-1$ 个位置将包含 $L$ 中前 $i-1$ 小的元素，并按升序排列。在第 $i$ 次迭代中，算法会反转从第 $i$ 个位置到当前第 $i$ 小元素所在位置的子列表。这将使第 $i$ 小的元素最终位于第 $i$ 个位置。

例如，对于一个包含 4 个元素的列表，算法将执行 3 次迭代。以下是处理 $L = [4, 2, 1, 3]$ 的过程：

1. $i = 1$，$j = 3 \longrightarrow L = [1, 2, 4, 3]$
2. $i = 2$，$j = 2 \longrightarrow L = [1, 2, 4, 3]$
3. $i = 3$，$j = 4 \longrightarrow L = [1, 2, 3, 4]$

在我们的架构中，执行该算法最耗时的部分是 Reverse 操作。因此，我们衡量每次迭代成本的标准仅仅是传递给 Reverse 的子列表长度，即 $j - i + 1$。整个算法的成本是每次迭代成本的总和。

在上述示例中，迭代成本依次为 3、1 和 2，总成本为 6。

给定初始列表，计算执行 Reversort 的成本。

## 说明/提示

**样例解释**

样例 #1 已在题目描述中说明。

在样例 #2 中，仅有一次迭代，Reverse 操作应用于长度为 1 的子列表，因此总成本为 1。

在样例 #3 中，第一次迭代反转了整个列表，成本为 7。此后列表已排序，但仍有 5 次迭代，每次成本为 1。

**数据范围**

**测试集 1（7 分，可见判定结果）**

- $1 \leq \mathbf{T} \leq 100$。
- $2 \leq \mathbf{N} \leq 100$。
- $1 \leq \mathbf{L}_{i} \leq N$，对所有 $i$ 成立。
- $\mathbf{L}_{i} \neq \mathbf{L}_{j}$，对所有 $i \neq j$ 成立。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
4
4 2 1 3
2
1 2
7
7 6 5 4 3 2 1```

### 输出

```
Case #1: 6
Case #2: 1
Case #3: 12```

# 题解

## 作者：Sweet_2013 (赞：7)

排序的方法是这样的：每次找到剩下数字中最小的那个，把从当前位置到这个最小数字之间的所有数字都倒过来，最后记录每次倒转用了多少成本。

开个循环，从第一个数字到倒数第二个，先假设当前数字是最小的，接着再写一个循环，用于找真正的最小数字，找完以后，把从当前位置到最小数字的位置倒过来，怎么倒呢？没错！题目已经提到了 reverse 这个好东西，那我们就用它倒喵！倒完之后，加上这次用的成本。两层循环结束后，就输出这一轮的答案，问题就解决了喵！


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,l[105],c;
int main() {
    cin>>t;
    while(t--){
    	c++;
        cin>>n;
        for(int i=0;i<n;i++) cin>>l[i];
        int ans=0;// 记录总共用了多少代价的 ans。
        for(int i=0;i<n-1;i++){
        	int minn=i;//假设当前数字是最小的
			for(int j=i+1;j<n;j++)if(l[j]<l[minn])minn=j;//找最小数字。
			reverse(l+i,l+minn+1);//把从当前位置到最小数字的位置倒过来。
			ans+=minn-i+1;//加上这次用的代价。
		} 
        cout<<"Case #"<<c<<": "<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Ghosty_Neutrino (赞：2)

## 题意
Reversort 算法的核心逻辑是从左到右遍历列表，每次找到当前位置到末尾的最小值，将其反转到当前位置，每次反转的成本为反转区间的长度，总成本为所有反转操作的成本之和，求出总成本。
## 分析
可以直接根据伪代码的逻辑实现。

假设数组从 $0$ 索引，从位置 $i=0$ 开始遍历到 $i=n-2$。

每次找到 $i$ 到 $n-1$ 范围内的最小值位置 $j$。
反转子数组 $i$ 到 $j$。

累加代价 $j-i+1$。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[110],t,n;
//反转数组的 [i,j] 区间
void reverse(int a[],int i,int j){
    while(i<j){
        swap(a[i],a[j]);
        i++;
        j--;
    }
}
int main(){
	scanf("%d",&t);
    for(int casen=1;casen<=t;casen++){
        scanf("%d",&n);
        //读取输入数组
        for(int i=0;i<n;i++) scanf("%d",&a[i]);
        int c=0;
        //模拟 Reversort 算法
        for(int i=0;i<n-1;i++){
            //寻找 i 到 n-1 范围内的最小值位置
            int minn=i;
            for(int j=i+1;j<n;j++){
                if(a[j]<a[minn]) minn=j;
            }
            //计算并累加代价
            c+=minn-i+1;
            //反转子数组 i 到minn
            reverse(a,i,minn);
        }
        //输出结果
        printf("Case #%d: %d\n",casen,c);
    }
    return 0;
}
```

---

## 作者：GeorgeDeng (赞：2)

很好的模拟题。

首先，我们得理解这个伪代码。

这个伪代码的含义是：枚举一个位置 $i$，再找到从 $i$ 到 $n$ 这个区间的最小值的位置，把这个区间全部反转。当 $i=n$ 的时候退出循环。

题目说如果反转 $i,j$ 两个位置，那么代价就加上 $j-i+1$。发现数据范围极小，所以我们直接暴力计算。

每一次，我们枚举这个 $i$，然后找到从 $i$ 往后的最小值的位置 $j$，然后 $ans\larr (j-i+1)+ans$，反转 $i,j$ 这个区间 ~~其实就是把伪代码翻译一遍~~。

然后，就没有然后了。

参考代码：

```cpp
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

int n;
int a[105];
int ans = 0;
void rev_sort(){
    for(int i = 1;i<n;i++){
        int minn = a[i];
        int pla = i;
        for(int j = i+1;j<=n;j++){
            if(a[j]<minn){
                minn = a[j];
                pla = j;//找到最小值
            }
        }
        ans+=pla-i+1;//记录答案
        reverse(a+i,a+pla+1);//反转
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int _;
    cin>>_;
    for(int i = 1;i<=_;i++){
        cin>>n;
        ans = 0;//多测不清空，爆0两行泪
        for(int i = 1;i<=n;i++){
            cin>>a[i];
        }
        rev_sort();
        cout<<"Case #"<<i<<": "<<ans<<endl;//注意特定的输出格式
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 前言
这是一道简单的模拟题，核心就是明白这个排序的方法。
## 思路
先找连续下降的序列，之后翻转，然后再累加迭代成本，最后统计输出即可。
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[105],ans; 
int Reversort()//计算Reversort排序迭代成本
{
    
    for(int i=1;i<n;i++)
    {
        int k=i;
        for(int j=i+1;j<=n;j++)
            if(a[j]<a[k])//找连续下降随后一个值（也就是最小值）的下标
                k=j;
        for(int l=i,r=k;l<r;l++,r--) //翻转
            swap(a[l],a[r]);
		ans+=(k-i+1);//累加
    }
    return ans;
}

int main()
{
    cin>>t;
    for(int i=1;i<=t;i++) 
    {
        cin>>n;
        for(int j=1;j<=n;j++)
            cin>>a[j];
        cout<<"Case #"<<i<<": "<<Reversort()<<"\n";//输出
        ans=0;//重置
    }
    return 0;
}
```
目前最优解

---

## 作者：bz029 (赞：0)

### 思路

由题目描述知，此题是让我们将长度为 $n$ 的数组用一种算法进行升序排序，算出其中反转的长度和。

此题的重点是理解题目中的伪代码，其含义大约是：

1. 初始化：从列表的第一个元素开始，逐步处理到倒数第二个元素。
2. 寻找最小值位置：在当前未排序部分（从第 $i$ 个元素到列表末尾）中找到最小值的位置 $j$。
3. 反转子列表：将从第 $i$ 个元素到第 $j$ 个元素之间的子列表进行反转。

用 c++ 来表示：

```cpp
for(int i=1;i<n;i++){
  int mi=i;//初始化 
  for(int j=i+1;j<=n;j++){
    if(a[j]<a[i]) mi=j;//寻找最小值位置 
  }
  ans+=mi-i+1;
  reverse(a+i,a+mi+1);//反转子列表
}
```

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;

int t,n,a[N],o;

void work(){
	int ans=0;//多测要清空 
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		int mi=i;//初始化 
		for(int j=i+1;j<=n;j++){
			if(a[j]<a[i]) mi=j;//寻找最小值位置 
		}
		ans+=mi-i+1;
		reverse(a+i,a+mi+1);//反转子列表
	}
	cout<<"Case #"<<o<<": "<<ans<<endl;//输出要注意格式 
}

signed main(){
	cin>>t;
	while(t--){
		o++;
		work();
	}
	
	return 0;
}

```

---

## 作者：Yi_chen123 (赞：0)

## 思路

此题我们可以进行简单模拟排序的过程，时间复杂度为 $O(Tn^2)$，如果用了 STL 的 `reverse()` 可能常数还很高，不过 $n,T \le 100$ 的数据范围是明显可以通过本题的。\
可能有人不理解排序的过程究竟是怎样的，我来为大家讲解一下：

- 首先有一个**迭代初始下标** $i$，它最开始是 $1$，每一次迭代结束后 $+1$，当 $i = n - 1$ 时停止迭代。
- 对于每一次迭代有如下步骤：
- - 从下标 $i$ 开始遍历数组，找出第 $i$ 至第 $n$ 个元素之中的最小值，最小值所在的下标记为 $idx$。
  - 反转 $a_i$ 至 $a_{idx}$ 中的所有元素。本次迭代的代价为 $idx - i + 1$。

然后就可以上暴力 AC 了。

```cpp
#include<bits/stdc++.h>
#define test(a) cout << #a << " = " << a << endl
#define int long long 
using namespace std;

int ar[114514]; 

int sol(int n){
	int ans = 0; 
	for(int i = 0; i < n - 1; ++i){
		int idx = i;
		for(int j = i; j < n; ++j) idx = (ar[j] < ar[idx] ? j : idx);
		ans += idx - i + 1;
		reverse(ar + i, ar + idx + 1); 
	} 
	return ans; 
} 
signed main(){
	int T; cin >> T;
    int Q = T;
	while(T--){
		memset(ar, 0, sizeof(ar)); 
        cout << "Case #" << Q - T << ": ";
		int n; cin >> n;
		for(int i = 0; i < n; ++i) cin >> ar[i];
		cout << sol(n) << endl; 
	} 
    return 0;
}
```

---

## 作者：jinfanhao (赞：0)

直接按题目模拟。\
题目大意：对一个序列进行 $n-1$ 次操作，每回找到这个序列第 $i+1$ 及以后比第 $i$ 个小的最小值，记录它的坐标，进行翻转。\
模拟过程：先将数组中 $i+1$ 以后最小值的位置找到，记录位置，然后翻转子序列，最后累加成本。\
另外，记得多测清空。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=101;
int t,n,op[N],sum;
int main(){
	scanf("%d",&t);
	for(int k=1; k<=t; ++k){
		sum=0;
		scanf("%d",&n);
		for(int i=1; i<=n; ++i)scanf("%d",&op[i]);
		for(int i=1; i<n; ++i){
			int pos=i;
			for(int j=i+1; j<=n; ++j){
				if(op[j]<op[pos])pos=j;
			}
			reverse(op+i,op+pos+1);
			sum+=(pos-i+1);
		}
		printf("Case #%d: %d\n",k,sum);
	}
	return 0;
}
```

---


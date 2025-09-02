# Inventory

## 题目描述

Companies always have a lot of equipment, furniture and other things. All of them should be tracked. To do this, there is an inventory number assigned with each item. It is much easier to create a database by using those numbers and keep the track of everything.

During an audit, you were surprised to find out that the items are not numbered sequentially, and some items even share the same inventory number! There is an urgent need to fix it. You have chosen to make the numbers of the items sequential, starting with $ 1 $ . Changing a number is quite a time-consuming process, and you would like to make maximum use of the current numbering.

You have been given information on current inventory numbers for $ n $ items in the company. Renumber items so that their inventory numbers form a permutation of numbers from $ 1 $ to $ n $ by changing the number of as few items as possible. Let us remind you that a set of $ n $ numbers forms a permutation if all the numbers are in the range from $ 1 $ to $ n $ , and no two numbers are equal.

## 说明/提示

In the first test the numeration is already a permutation, so there is no need to change anything.

In the second test there are two pairs of equal numbers, in each pair you need to replace one number.

In the third test you need to replace $ 2 $ by $ 1 $ , as the numbering should start from one.

## 样例 #1

### 输入

```
3
1 3 2
```

### 输出

```
1 3 2 
```

## 样例 #2

### 输入

```
4
2 2 3 3
```

### 输出

```
2 1 3 4 
```

## 样例 #3

### 输入

```
1
2
```

### 输出

```
1 
```

# 题解

## 作者：zajasi (赞：5)

感觉好像没有类似思路的，所以来发一篇。
## 题意
用最少的次数，将原数组修改成一个排列。问修改后的数组是什么？
## 解题思路
首先，可以标记出在原数组中哪些位置上的数是重复出现的（第一次出现的不用记），以及出界的数的位置。

然后，扫一遍排列，看看在排列中哪些数没出现过。

最后的最后，将重复出现的数改成没有出现过的数。

观察到 $a_i$ 的范围很小，只有 $100000$，所以直接标记哈希就行了。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a[100010],h[100010];//h 记录哈希
vector<int> d,v;
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        h[a[i]]++;//统计出现的次数
        if(h[a[i]]>1||a[i]>n)d.push_back(i);//d 记录在原数组中重复出现或出界了的数的位置
    }
    for(int i=1;i<=n;i++){
        if(h[i]==0)v.push_back(i);//v 记录在排列中没有出现过的数
    }
    for(int i=0;i<d.size();i++){
        a[d[i]]=v[i];//将重复的数换成没有出现的数
    }
    for(int i=1;i<=n;i++){
        cout<<a[i]<<" ";//直接输出结束
    }
    return 0;
}
```

---

## 作者：Ninelife_Cat (赞：2)

贪心。

如果一个数已经符合条件，那么我们就不用修改它。

否则我们把它修改为排列中还没有出现过的数就行了。

核心代码：
```cpp
const int N=1e5+10;
int n,a[N],cnt[N];
queue<int> q;//用队列存放排列中未出现过的数
signed main()
{
	n=read();
	for(ri int i=1;i<=n;++i)
		++cnt[a[i]=read()];//cnt记录每个数字的出现次数
	for(ri int i=1;i<=n;++i)
		if(!cnt[i]) q.push(i);
	for(ri int i=1;i<=n;++i)
		if(cnt[a[i]]==1&&a[i]<=n) cout<<a[i]<<" ";//如果符合条件,直接输出
			else --cnt[a[i]],cout<<q.front()<<" ",q.pop();//修改
	return 0;
}

---

## 作者：Zq_water (赞：1)

**贪心思路**

如果这个数在 $1 \sim n$ 的序列出现了，就不修改。

否则给他修改成还没有出现的数。

每次拿一个桶数组标记就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[100005],ans[100005],len;
bool t[100005];

int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],t[a[i]]=true;
    
	for(int i=1;i<=n;i++)
		if(!t[i]) ans[++len]=i;
 
	memset(t,false,sizeof t);
	len=0;
	for(int i=1;i<=n;i++){
		if(t[a[i]]||a[i]>n) cout<<ans[++len]<<" ";
		else cout<<a[i]<<" ";
		t[a[i]]=true;
	}
	return 0;
}
```

---

## 作者：LiJinLin_AFO (赞：0)

# CF569B 题解

so easy!


------------
## 正文开始

本题比较简单，使用一个桶存储 $a_1 \sim a_n$ 出现的个数，再从下标 $1 \sim n$ 遍历，每个数 $a_i$ 分两种情况：

1. 只存在一次且 $1 \le a_i \le n$。这种情况直接输出 $a_i$ 即可。

2. （存在多次且 $1 \le a_i \le n$）或者 $a_i < 1$ 或者 $a_i > n$。在程序开头设一个变量 $cnt=1$，用来遍历数组 $a$。遇到这种情况，找出第一个数 $num$，满足 $num \ge cnt$ 且 $num \le n$ 且 $num$ 在数组 $a$ 中并未出现。输出 $num$。将 $num$ 赋给 $cnt$，将存放 $a_i$ 的桶的值减 $1$，再将存放 $num$ 的桶的值变为 $1$，表示已经输出 $num$。

虽然测试样例与给出的输出样例不同，但本题中有详细说明：只需要给出一种情况即可。

上代码：
```cpp
#include<stdio.h>
int a[100005],t[100005],cnt=1;
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		t[a[i]]++;//计算桶的值
	}
	for(int i=1;i<=n;i++){
		if(t[a[i]]==1&&a[i]>=1&&a[i]<=n){
			printf("%d ",a[i]);
			continue;
		}//第一种情况
		if(t[a[i]]>1||a[i]>n||a[i]<1){
			while(cnt<=n&&t[cnt]) ++cnt;
			printf("%d ",cnt);
			++t[cnt],--t[a[i]];
		}//第二种情况
	}
	return 0;
} 
```
注：请勿抄袭！

---

## 作者：_Execution_ (赞：0)

### 分析

题意：输入一个长度为 $n$ 的数组 $a$，要求把 $a_i$ 替换成 $1 \sim n$ 中的数，要求不重复，不遗漏。

### 思路

题目说了要以**最小的修改次数**，
那么如果当前元素已经符合要求，就不必修改；
否则就修改，
由此达到最小修改的次数。
我们在每次输入 $a_i$ 时判断是否小于等于 $n$，并且第一次出现。
若是就把结果保存在 $res$ 数组中。
然后再遍历一遍 $res$ 数组，处理那那些未处理的。
在标记数组中找到最小的没用过的数字。

### 细节:

1. 把储存修改后数组 $res$ 初始化为 $-1$，便在后面进行填充。

2. 在遍历计数数组 $cnt$ 来填充空缺的地方时，
可以定义一个变量 $start$，
每次找到未使用过的数时标记所在的下标的后一位,
下次继续从这里开始往下找。

### code:

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//引用命名空间
const int N=100000+10;//定义数组大小
int n;
int a[N];//原数组
bool cnt[N];//判断是否出现
int res[N];//修改后数组b 
int main(){
    memset(res,-1,sizeof(res));//初始化
    memset(cnt,0,sizeof(cnt));//初始化
    cin>>n;//输入n
    for(int i=0;i<n;i++){//开始读入数组
        cin>>a[i];//输入数组
        if(!cnt[a[i]]&&a[i]<=n){//判断是否出现以及是否在范围内
            res[i]=a[i];//不用修改
            cnt[a[i]]=true;//标记已经出现
        }
    }
    int start=1;//开始找的数
    for(int i=0;i<n;i++){//开始便利res数组
        if(res[i]==-1){//如果需要修改
            for(int j=start;j<=n;j++){//从上次找的地方继续找
                if(!cnt[j]){//如果未被标记
                    start=j+1;//下次从这里找
                    res[i]=j;//修改
                    cnt[j]=true;//标记
                    break;//找到了直接退出
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        cout<<res[i]<<" ";//输出res
    }
    // system("pause");
    return 0;
}
```



---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF569B) & [CF链接](http://codeforces.com/problemset/problem/569/B)

## 思路分析：

这道题我的思路思维能力比较强，首先开一个 $a$ 数组存储数列，$b$ 数组时布尔类型，相当于一个桶，用来存储每个数有没有出现过，$c$ 数组用来存储那些位置重复出现过可以被修改，最后一个队列 $q$ 存储需要修改哪些数。

有了这些，相信很容易就得出代码了。

## 代码：

```cpp
#include<iostream>
#include<queue>
using namespace std;
int n,a[100010];
bool b[100010],c[100010];
queue<int>q;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(b[a[i]]||a[i]>n){//如果这个数之前已经出现过或者大于n也就是不在n的全排列之间
			c[i]=true;//就可以被修改
		}
		b[a[i]]=true;//桶代表a[i]出现过
	}
	for(int i=1;i<=n;i++){
		if(b[i]==false){//如果i没有出现过
			q.push(i);//就入队，表示i需要修改
		}
	}
	for(int i=1;i<=n;i++){
		if(c[i]){//如果这个位置可以被修改
			if(q.size()){
				a[i]=q.front();//就从队列里拿出需要修改的元素，进行修改
				q.pop();
			}
		}
		if(q.empty()){//如果已经没有要修改的元素了
			break;//就break
		}
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";//输出
	}
	return 0;
}
```

---

## 作者：sz_wsy (赞：0)


#### [CF569B Inventory  题目传送门](https://www.luogu.com.cn/problem/CF569B)

## 前置知识
本题需要用到 STL 中的队列。队列，是一种先进先出的数据形式。其基本操作如下：
```cpp
queue<int>q;//该队列只存放int型元素，名称为q
q.empty()   //如果队列为空则返回 1，否则返回 0
q.push(x)   //向队列中加入一个元素 x
q.pop()     //将队首弹出
q.front()   //返回队首元素
q.size()    //返回此时队列内元素个数
q.back()    //返回队尾元素
```

## 题目大意

给定一个长度为 $n$ 的数组 $a$，满足 $1\le a_i\le n$，要求最小修改次数，使其成为 $1$ 到 $n$ 的排列，输出修改后的数组。其中，$1\le n\le 10^5$，$1\le a_i\le 10^5$。

## 算法分析
- 不难发现重复的数字要更改，且大于 $n$ 的数字也要更改。
- 遍历 $a$ 数组，若满足 $1\leq a_i\leq n$，就将 $b_{a_i}$ 记为 $1$（$b$ 相当于一个桶），若是 $a$ 数组中**第一次**出现 $a_i$，则标记 $f_i$ 为 $1$。$f_i$ 为 $1$，表示这一位不用改动，否则要改动。
- 枚举 $1\sim n$，若 $b_i$ 为 $0$，就将 $i$ 放入队列（队列中存放原数组中没有的、要补上的数字）。
- 最后输出时，如果 $f_i$ 为 $0$，输出队列头元素，否则输出 $a_i$ 即可。

## 代码呈现
```cpp
#include <iostream>
#include <queue>
using namespace std;
const int N = 1e5+3;
int a[N],n;
bool b[N],f[N];
queue<int>q;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]>=1 && a[i]<=n){  //这一位符合要求，不用改动 
			if(b[a[i]]==0)
				f[i]=1;			//第一次出现 
			b[a[i]]=1;
		}
	}
	for(int i=1;i<=n;i++){
		if(!b[i]){
			q.push(i);  //队列中存放原数组中没有的、要补上的数字
		}
	}
	for(int i=1;i<=n;i++){
		if(f[i]) cout<<a[i]<<" ";  //这一位不用改动 
		else {                     //这一位替换成q中的数字 
			cout<<q.front()<<" ";
			q.pop();
		}
	}
	return 0;
}
```



---

## 作者：封禁用户 (赞：0)

# 题目描述

[Inventory](https://www.luogu.com.cn/problem/CF569B)

## 注意事项

本题需要用 STL 库里的队列，不知道的同学可以[点这里](https://blog.csdn.net/weixin_44572229/article/details/120016366)。

# 算法思路

定义 $cnt_{i}$ 表示 $i$ 在 $a$ 数组里出现的次数。如果为 $0$，则放入要替换的队列里。

枚举 $1 \sim n$，如果 $a_{i}$ 是第一次出现的，输出 $a_{i}$，否则输出队列的头结点。

### 时间复杂度：$O(n)$。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=100010;
ll n,m,x,a[N],cnt[N];
queue<ll> que;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]>=1&&a[i]<=n)
		{
			cnt[a[i]]++;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(cnt[i]==0)
		{
			que.push(i);
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]<1||a[i]>n)
		{
			cout<<que.front()<<" ";
			que.pop();
		}
		else if(cnt[a[i]]==1)
		{
			cout<<a[i]<<" ";
		}
		else
		{
			cout<<que.front()<<" ";
			que.pop();
			cnt[a[i]]--;
		}
	}
	return 0;
}
```

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难发现重复的数字是需要更改的，并且大于 $n$ 的数字也是需要更改的。  

我们不妨把 $1$ 到 $n$ 中未出现的数都存储到 $ans$ 数组里，每当遇到一个需要更改的数时，我们就输出 $ans$ 数组里的下一个数。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],ans[100005],len;
bool f[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[a[i]]=true;
	}
	for(int i=1;i<=n;i++){
		if(!f[i]){
			ans[++len]=i;
		}
	}
	memset(f,false,sizeof(f));
	len=0;
	for(int i=1;i<=n;i++){
		if(f[a[i]]||a[i]>n){
			cout<<ans[++len]<<" ";
		}
		else{
			cout<<a[i]<<" ";
		}
		f[a[i]]=true;
	}
	return 0;
}
```


---

## 作者：zwy__ (赞：0)

### 题目意思
给你一个长度为 $n$ 的数组 $a$，满足数组 $1 \le a_i \le n$，要求使数组的数成为 $1$ 到 $n$ 的数中的一个并且两两不相同，输出修改后的数组（每个数中间用空格隔开。）。

满足 $1 \le n \le 10^5$ 且 $1 \le a_i \le 100000$。
### 题目思路
PS：
+ 我们输出一个最简单的解即可。
+ 这道题似乎没有用 set 的题解，我来发一篇。
+ 在洛谷上提交老是 UKE，这里我发一下 CodeForces 上的记录。

进入正题，可以看到数据范围比较小，所以可以用数组记录当前的数是否出现过，在根据题目要求对原数组进行赋值即可。可以将不符合要求的数进行特殊标记，最后将没有出现过的数赋值给不符合要求的数，就解决了。

这道题如果直接做的话会超时，所以我们可以用 STL 优化，很多大佬都用了队列，我这里用一下 set，完全不会超时。

具体操作是：第一步，我们将所有数插入 set，方便我们赋值操作。第二步，我们遍历一次数组，对于每个数，用数组计数判断这个数是否是第一个出现。如果已经出现，就在 set 里面删除掉这个数，并对这个数进行特殊的标记。最后一步，我们把特殊标记的数变成没有出现过的数，我们的答案就好了。
### 细节
+ 我们需要用快读函数进行优化，否则数据会让你超时。
+ 在使用 set 时，访问具体的数要在前面加上星号，这样才能访问到具体的数，而不是访问到地址，从而导致程序错误。

[保证代码正确](https://codeforces.com/problemset/submission/569/198892998)
### AC的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int a[100005],b[100005];
set<int>se;
int main()
{
	scanf("%lld",&n);
	for(int i=1; i<=n; i++)se.insert(i);
	for(int i=1; i<=n; i++)
	{
		scanf("%d",&a[i]);
		if(b[a[i]]==0&&a[i]<=n&&a[i]>=1)
		{
			b[a[i]]=1;
			se.erase(a[i]);
			continue;
		}
		a[i]=-1;
	}
	for(int i=1; i<=n; i++)
	{
		if(a[i]==-1)
		{
			a[i]=(*se.begin());
			se.erase(*se.begin());
		}
	}
	for(int i=1; i<=n; i++)printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：diqiuyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF569B)

**思路**

既然是 $1$ 到 $n$ 的排列，那显然 $1$ 到 $n$ 的每一个整数都应该出现有且仅有 $1$ 次。显然，对于 $1$ 到 $n$ 中哪些只出现了 $1$ 次的数，可以直接输出。而对于超过 $1$ 次的哪些，应当只输出 $1$ 次。只要用一个用于统计出现次数的数组 $tim$ 来维护即可。但是对于而对于没有出现过的那些，不妨再另建一个数组 $ans$ 来存储，或者用链表之类的东西也可以。总之，对于每个使得 $cnt_{a_i}>1$ 的或者是 $a_i>n$ 的 $i$，应该把部分 $a_i$ 替换成 $ans_i$。

**MAIN CODE**
```cpp
for(int i=1;i<=n;i++)
    printf("%d ",((tim[a[i]]--)==1&&a[i]<=n)?a[i]:ans[cnt--]);
    //这里解释一下，之所以要 tim[a[i]]-- 是因为第二种情况所需
    //而这个操作并不会影响第一种情况
    //简单来说就是省代码
```
~~又水了一篇题解。~~

---

## 作者：lnkkerst (赞：0)

~~大水题，看没人发题解赶紧水一发~~

题意：给你n个编号，要求以最小的修改次数使其成为一个从1到n的排列，并输出这个排列（所有的数字都在1到n的范围内且没有两个数字相同）。

手动模拟一遍即可，思路都贴在注释里了。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int a[100001]; //存储所给的编号
bool b[100001]; //标记编号是否出现过

int main() {
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        if(b[a[i]] || a[i] > n) a[i] = 0; //如果编号之前出现过或编号大于n则将其置为0（标记要改的位置）
        if(a[i] <= n) b[a[i]] = true; //标记编号出现
    }
    int pos = 0;
    for(int i = 1; i <= n; ++i) {
        while(b[pos]) ++pos; //从小到大寻找所给的编号中没有出现过的编号
        if(!a[i]) a[i] = pos, b[pos] = 1; //修改编号，标记已出现
    }
    for(int i = 1; i <= n; ++i) cout << a[i] << ' '; //输出！
    return 0;
}
```


---

## 作者：zhangyuhao9 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF569B)

题意
-
~~这题是真的水~~，题目给你从 $1$ 到 $n$ 共 $n$ 个不重复的编号（推理得），要求以最小的修改次数使其成为一个从 $1$ 到 $n$ 的排列，并输出这个排列。

**思路**
-
重要的事情说三遍:大模拟！大模拟！大模拟！显然，对于 $1$ 到 $n$ 中哪些只出现了 $1$ 次的数，可以直接输出。所以可以用一个数组存储编号，再用布尔数组标记编号是否出现过。而对于超过 $1$ 次的哪些，应当只输出 $1$ 次。如有不符合的标记为 $0$。代码里有说

剩下的看代码和注释吧！

**CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[100001],pos=0;//pos为编号
bool b[100001];
//如上所说两个数组
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];//输入
        if(b[a[i]]||a[i]>n)//判定条件，左边为出现过的，右边为编号大于n的，即不符合的
            a[i] = 0;//全部标记为0
        if(a[i]<=n)
            b[a[i]]=true;//枚举满足条件
    }
    for(int i=1;i<=n;++i){
        while(b[pos])
            ++pos;
        if(!a[i]) 
            a[i]=pos,b[pos]=1;//核心部分
    }
    for(int i=1;i<=n;++i) 
        cout<<a[i]<<' ';
    return 0;
}
```
求过！

---

## 作者：wangyibo201026 (赞：0)

# 思路讲解

大致思路：首先标记每一个数，如果有重复出现，就把它改成没有出现过的数。

细节：拿一个队列去存储没有出现过的数，由于题目说明输出任意一种排列即可，所以当一个数出现过时，取出队首，替换掉这个数字，当跑完一遍时，输出现有序列即可。

# 代码

代码加注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[100005];
int a[100005],cnt[100005];
int n;
queue<int> q;    //存储没有出现的
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		cnt[a[i]]++;    //次数
		vis[a[i]]=true;   //标记
	}
	for(int i=1;i<=n;i++)
		if(vis[i]==false) q.push(i);
	for(int i=1;i<=n;i++)
	{
		if(cnt[a[i]]==1&&a[i]<=n) cout<<a[i]<<" ";    //当重复出现时，由于数据有bug，所以要判a[i]<=n
		else
		{
			cout<<q.front()<<" ";    //输出没出现过的
			q.pop();     //pop掉
			cnt[a[i]]--;      //注意，次数一定要--
		}
	}
	return 0;
}
```

---


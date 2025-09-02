# [PA 2024] Znaczki pocztowe

## 题目背景

PA 2024 2C

## 题目描述

**题目译自 [PA 2024](https://sio2.mimuw.edu.pl/c/pa-2024-1/dashboard/) Runda 2 [Znaczki pocztowe](https://sio2.mimuw.edu.pl/c/pa-2024-1/p/zna/)**

Byteasar 曾经收集了大量邮票。然而，他对邮票的兴趣已不如年轻时，因此他决定将自己的邮集赠送给更年轻的集邮爱好者。不过，他希望尽可能公平地完成这项工作，为此他需要你的帮助。

Bytesar 的邮集由 $n$ 张邮票组成，其中第 $i$ 张来自城市 $a_i$。为简单起见，我们用整数表示这些城市。Byteasar 打算在报纸上刊登一则公告，宣布他计划赠送自己的收藏的邮票。如果有 $k$ 个人愿意接收，他将在如下条件下向每个人赠送一个邮票的子集：每个人都必须收到相同的邮票多重集。这就意味着，对于每两个申请人和每个城市，两个申请人都必须从该城市获得相同数量的邮票。特别地，这可能意味着 Byteasar 将不发放任何邮票。

Byteasar 不知道会有多少人前来接收。因此，对于 $1$ 到 $n$ 范围内的每个数 $k$，你需要找出如果有 $k$ 个人愿意接收，Byteasar 最多可以分发多少张邮票。

## 说明/提示

如果有一个人愿意接收，Byteasar 可以把所有邮票都给他。

如果有两个人，Byteasar 可以给他们每人两张 $1$ 号城镇的邮票、一张 $42$ 号城镇的邮票和一张 $777$ 号城镇的邮票，即总共 $8$ 张邮票。

如果有四个人，Byteasar 可以给他们每人一张 $1$ 号城市的邮票。

如果愿意接收的人数超过四人，Byteasar 将无法送出任何邮票。

## 样例 #1

### 输入

```
9
1 1 777 42 777 1 42 1 777
```

### 输出

```
9 8 6 4 0 0 0 0 0
```

# 题解

## 作者：WindowsWKP (赞：5)

Update On 4.25：修改为全角符号。

Update On 5.5：代码全部修改为 ```scanf``` 和 ```printf``` 。（避免剪枝部分歧义）

Update On 7.28：“剪枝”板块改为“优化”板块。

# 分析
这道题目最基础的枚举思路是：

1. 用桶 $f$ 存下每一种邮票出现的数量。

2. 从 $1$ 到 $n$ 枚举 $k$。

3. 从 $1$ 到 $n$ 判断 ${f}_{i}$ 共有几张可用的邮票。

4. 合成答案，输出结果。

但由于 ${a}_{i}$ 太大，无法存下太大的桶，所以一个简单的处理方式就是**离散化**，代码 $60$ 分。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300010],n,k,x,y,f[300010],ans;
int main(){
    cin>>n;
    for (int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    for (int i=1;i<=n;i++){
        if (a[i]!=y)
            x++,y=a[i];
        a[i]=x;
    }
    for (int i=1;i<=n;i++)
        f[a[i]]++;
    for (k=1;k<=n;k++){
        ans=0;
        for (int i=1;i<=n;i++)
            if (f[i]>=k)
                ans+=f[i]-f[i]%k;
        cout<<ans<<" ";
    }
    return 0;
}
```
# 优化
这种代码需要排序，又有大规模枚举，必须要优化。
1. 使用 ```printf``` 代替 ```cout``` ，代码 $60$ 分。

2. 将 $ans$ 改为数组，如果 ${ans}_{k-1}$ 已经是 $0$ 了，就没有继续枚举的必要了。虽然还是 $60$ 分，但子任务 $7,8,9,10$ 开始出现很多通过的点了。

3. 边离散化边装桶，代码还是 $60$ 分，但仍有较小提升，且更为简洁。

4. 判断 ${ans}_{k}$ 时，只判断 $1$ 到 $x$，因为装了东西的桶只有 $x$ 个。代码 $90$ 分，**只剩下 $2$ 个点**。

5. 对桶进行排序，并在判断 ${ans}_{k}$ 时，如果发现桶已经无法取出邮票了，就停止判断。代码 $100$ 分，且有极大余量。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300010],n,k,x,y,f[300010],ans[300010]={1};
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for (int i=1;i<=n;i++){
        if (a[i]!=y)
            x++,y=a[i];
        a[i]=x;
        f[a[i]]++;
    }
    sort(f+1,f+x+1);
    for (k=1;k<=n;k++){
        ans[k]=0;
        if (ans[k-1]==0)
            break;
        for (int i=x;i>=1;i--){
            if (f[i]>=k)
                ans[k]+=f[i]-f[i]%k;
            else
                break;
        }
        printf("%d ",ans[k]);
    }
    for (k=k;k<=n;k++)
        printf("0 ");
    return 0;
}
```

---

## 作者：xyx404 (赞：3)

## 思路：
规律：观察后发现答案是每种邮票的张数除以现在的人数后省去小数部分后再次乘以人数。

每种邮票的张数除以现在的人数后省去小数部分就是可以分成几组，组不能是小数，因为题中说申请人都必须从该城市获得相同数量的邮票所以不能分开。

再乘以人数就是求分出了几张邮票。

一开始想用桶但发现数据太大了开不了数组，所以用了 `map` 但是用了 `map` 后发现不能满分于是观察了下发现只要有一个的邮票发出总和为零时，后面的也都是零，这样过后发现还是不可以满分，再次观察题目发现是不需要排序的，所以把 `map` 改成 `unordered_map` 就这样了吗，没有，再次观察可以发现当一个邮票的张数已经小于现在的人数了，那么不管怎么样，后面都不可以让答案增加了，所以直接删去，这样就可以了。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
unordered_map<int,int>mp;
int n;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		int a;cin>>a;
		mp[a]++;
	}
	bool s0=0;// 特判 0 
	for(int i=1;i<=n;i++){
		long long sum=0;
		if(s0){// 特判 0 
			cout<<"0 ";continue;
		}
		auto it=mp.begin();
		while(it!=mp.end()){
			sum+=(it->second)/i*i;
			if((it->second)<i)mp.erase((it++));// 直接删去 
			else it++;
		}
		cout<<sum<<" ";
		if(sum==0)s0=1;// 特判 0 
	}
	return 0;
}
```

---

## 作者：zhengpie (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P10355)

### 1.思路

考虑使用桶的思想记录每个来自每个城市的邮票的数量。因为城市的编号可能较大，于是使用 ```map``` 容器进行存储。（不知道 ```map``` 的同学，请点[这里](https://oi-wiki.org/lang/csl/associative-container/)）

然后，对于每一个城市的邮票，记其为 $m_i$。考察每个人数 $k$，容易知道，对于城市 $i$，Byteasar 可以送出 $m_i - m_i \bmod k$ 张邮票。

于是，暴力枚举即可。

### 2.细节

什么“暴力枚举即可”？你没考虑时间复杂度吗？

显然，我们发现，当 $m_i > k$ 时，$m_i - m_i \bmod k = 0$！于是，对于上述的这种情况，我们就不考虑 $m_i$。（反正它初始化的时候就是零，现在也是零，所以可以不枚举。）

这样，就不会超时了！

### 3.完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[1919810];
map<int,int> m;
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i = 1,x;i <= n;i++) {cin>>x;m[x]++;}
	for(auto i : m)//使用auto遍历map中的元素
		for(int j = 1;j <= i.second;j++)//注意是map对应的value值，而不是key！
			a[j] += i.second - i.second % j;
	for(int i = 1;i <= n;i++) cout<<a[i]<<" ";
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

每种邮票之间毫无关系，做出的贡献只与个数有关。

假设某种邮票的个数为 $x$，如果此时有 $i$ 个人愿意接受，那么可以发出 $\left\lfloor\dfrac{x}{i}\right\rfloor \cdot i$ 张邮票，因为每个人都要得到等量邮票。

那怎么统计答案呢？其实直接按照前面说的扫一遍就可以了，因为邮票总数加起来只有 $n$。当然也可以用数论分块优化，你看上面那个下取整就很典，直接对相同的一段区间加，最后单点查，过程可以用差分与前缀和维护。

唉唉，不管最后这块怎么优化，瓶颈在于读入的每个数出现次数的统计。因为值域达到 $10^9$，可以考虑离散化或者直接使用 `std::map` 与 `std::unordered_map` 进行打桶标记。

# Code
```cpp
//直接扫一遍的代码
#include<bits/stdc++.h>
std::unordered_map<int,int>mp;
int ans[300005];
int n;
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;++i)
		scanf("%d",&x),++mp[x];
	for(const auto&i:mp)
		for(int j=1;j<=i.second;++j)
			ans[j]+=i.second/j*j;
	for(int i=1;i<=n;++i)
		printf("%d ",ans[i]);
	return 0;
}
```
```cpp
//数论分块的代码
#include<bits/stdc++.h>
std::unordered_map<int,int>mp;
int ans[300005];
int n;
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;++i)
		scanf("%d",&x),++mp[x];
	for(const auto&i:mp)
		for(int l=1,r;l<=i.second;l=r+1)
			r=i.second/(i.second/l),ans[l]+=i.second/l,ans[r+1]-=i.second/l;
	for(int i=1;i<=n;++i)
		printf("%d ",(ans[i]+=ans[i-1])*i);
	return 0;
}
```

---

## 作者：六楼溜刘 (赞：1)

### 题意

- 有若干个盒子，每个盒子里有若干个小球，小球总数为 $n$。输入方式是输入每个小球所在盒子的序号 $a_i$。
- 令 $i$ 号盒子中有 $b_i$ 个小球，对于所有 $k\in [1,n]$，求出 $\sum b_i-b_i\bmod k$。
- $1\le n\le 3\times 10^5,1\le a_i \le 10^9$

### 题解

这道题乍一看很困难啊。但是容易发现，当 $k>b_i$ 时，$i$ 号盒子就无法产生任何贡献了。并且容易发现 $\sum b_i$ 是 $O(n)$ 的。

所以对于每个盒子，求出它对 $1\le k \le b_i$ 的所有 $k$ 的贡献然后累加即可。因为要离散化或者用 `map` 之类的东西，复杂度 $O(n\log n)$。

### code

```cpp
const int N=3e5+5,inf=0x3f3f3f3f;
int n,ans[N];
map<int,int> mp;
signed main(){
	n=read();//芝士快读
	forup(i,1,n){
		int a=read();
		++mp[a];
	}
	for(auto i:mp){
		forup(j,1,i.second){
			ans[j]+=i.second-i.second%j;
		}
	}
	forup(i,1,n){
		printf("%d ",ans[i]);
	}
}
```

---

## 作者：Six_chestnuts (赞：0)

# 题目链接

[题目链接](https://www.luogu.com.cn/problem/P10355)

# 分析

~~本想着打个暴力的，没想到过了！~~

由于本题过于简单，就直接讲方法了。

开一个桶来统计编号的数量，再开一个数组，来存邮票的编号和数量，再排一遍序，再暴力输出即可，具体看代码。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int a[N],n,tot;
map<int,int> cnt;
struct node
{
	int num,c;
}b[N];
bool cmp(node x,node y)
{
	return x.c>y.c;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		cnt[a[i]]++;
		if(cnt[a[i]]==1)
			tot++,b[tot].num=a[i];
	}
	for(int i=1;i<=tot;i++)
	{
		b[i].c=cnt[b[i].num];
	}
	sort(b+1,b+1+tot,cmp);
	cout<<n<<" ";
	for(int i=2;i<=n;i++)
	{
		int ans=0;
		for(int j=1;j<=tot;j++)
		{
			if(b[j].c/i==0)
				break;
			ans+=b[j].c-b[j].c%i;
		}
		cout<<ans<<" ";
	}
	return 0;
}
```

---


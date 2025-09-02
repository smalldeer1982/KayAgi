# Hackers and Neural Networks

## 题目描述

黑客们再次尝试利用神经网络的输出来创造有趣的短语。这次，他们希望获得一个长度为 $n$ 的字符串数组 $a$。

最初，他们有一个长度为 $n$ 的数组 $c$，其中所有位置都是空白，用符号 $*$ 表示。例如，如果 $n=4$，那么初始时 $c=[*,*,*,*]$。

黑客们可以访问 $m$ 个神经网络，每个神经网络都有自己对请求的答案版本——一个长度为 $n$ 的字符串数组 $b_i$。

黑客们试图通过以下操作从数组 $c$ 得到数组 $a$：

1. 选择一个神经网络 $i$，它将执行对数组 $c$ 的下一个操作：随机选择一个空白位置（例如位置 $j$），并将 $c_j$ 替换为 $b_{i, j}$。例如，如果选择第一个神经网络且 $c = [*, \text{«like»}, *]$，而 $b_1 = [\text{«I»}, \text{«love»}, \text{«apples»}]$，那么经过第一个神经网络的操作后，$c$ 可能变为 $[\text{«I»}, \text{«like»}, *]$ 或 $[*, \text{«like»}, \text{«apples»}]$。
2. 选择一个位置 $j$，并将 $c_j$ 替换为空白。

不幸的是，由于黑客访问神经网络的方式，他们只能在所有操作完成后看到修改后的数组 $c$，因此他们必须提前指定完整的操作序列。

然而，神经网络的随机行为可能导致无法获得目标数组 $a$，或者需要过多的操作才能获得它。

因此，黑客们希望你能帮助他们选择一个操作序列，确保以最少的操作次数获得数组 $a$。

更正式地说，如果存在一个操作序列可以确保从数组 $c$ 得到数组 $a$，那么在所有这样的序列中，找出操作次数最少的序列，并输出其中的操作次数。

如果不存在将数组 $c$ 转换为数组 $a$ 的操作序列，则输出 $-1$。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3 3
I love apples
He likes apples
I love cats
They love dogs
3 2
Icy wake up
wake Icy up
wake up Icy
4 3
c o D E
c o D s
c O l S
c o m E
4 5
a s k A
d s D t
O R i A
a X b Y
b a k A
u s k J```

### 输出

```
5
-1
6
8```

# 题解

## 作者：Gaochenxi103_QWQ (赞：0)

~~橙题，不能再多了。~~
## 题目概要
> 给你一个目标结果和一些包含部分目标结果的字符串数组，问你最少多少次操作可以得到目标结果。

### 样例解释
```
3 3
I love apples
He likes apples
I love cats
They love dogs
```

我们的目标是```I love apples```。

我们先选择第二个```I love cats```并操作 $3$ 保证一定可以将当前值变成```I love cats```。接着，我们再将第 $3$ 个字符串```cats```改成空格，再选择第一个```I love apples```使随机操作只能改第 $3$ 个位置的空格。因此一共 $5$ 次操作。

## 做法
我们可以先选择一个与目标最接近的值，并执行 $n$ 次，然后一次修改每个不一样的位置。

对于修改一个不一样的位置，我们执行两次操作，先将这个位置变成空格，然后再改就行了。

所以最后答案就是。

$$n+(n-(n-m)\times 2)$$

$n$ 是长度，$m$ 是最大与目标的相识度。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=510;
int T,n,m;
string a[N],c[N];
string b[N][N];
bool vis[N];
signed main()
{
    ios::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    cin>>T;
    while(T--)
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++)cin>>a[i];
        memset(vis,0,sizeof vis);
        int maxn=-1;
        bool flag=1;
        for(int i=1;i<=m;i++)
        {
            int cnt=0;
            for(int j=1;j<=n;j++)
            {
                cin>>b[i][j];
                if(b[i][j]==a[j]) vis[j]=true,cnt++;
            }
            maxn=max(cnt,maxn);
        }

        for(int i=1;i<=n;i++)flag&=vis[i];
        if(!flag)
        {
            cout<<-1<<"\n";
            continue;
        }        
        // cout<<maxn<<"\n";
        cout<<n+(n-maxn)*2<<"\n";
        
    }
}
```

---

## 作者：metrixgo_caozhendi (赞：0)

一道思路大于代码的题。一旦搞清如何操作剩下的问题就很简单了，甚至比 D 题代码都容易。

一开始我是这么想的：先填上第一个最正确的字符串，删掉错误部分，再填上对于空缺部分最正确的字符串，删掉错误部分，以此类推。但是有两个问题：一是找字符串的过程费时费力，也难以得证按照这样的顺序所需的字符串是最少的；二是看一眼第四组测试点，如果按照我们的想法，需要 $4+2+2+1+1=10$ 次操作，这是错误的。

根据第四组测试点，我们可以推出正确的操作思路：首先填上第一个最正确的字符串是对的，这里填上 ```bakA``` 作为示例；然后，我们没有必要删掉所有错的地方，只需要删一个填一个就行，这样每一次就只会在一个地方填，不受随机影响。所以这里我们依次删掉 ```b```，填上 ```a```，删掉位置二的 ```a```，填上 ```s``` 就可以了。

综上所述，我们只需要找到最正确的那个字符串先填上，剩下的错误部分删一填一就完成了目标。如果在目标字符串中有一个位置与其他字符串的该位置都不同，就说明无论怎么操作都无法填上该位置，那么就输出 ```-1``` 即可。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
int n,m,k,t,c,book[N],ans,flg;
string a[N],b[N][N];
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		flg=1,ans=0;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=m;i++) for(int j=1;j<=n;j++) cin>>b[i][j];
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(b[i][j]==a[j])
				{
					c++;
					book[j]=1;
				}
			}
			ans=max(ans,c);
			c=0;
		}
		for(int i=1;i<=n;i++)
		{
			if(book[i]==0) flg=0;
			book[i]=0;
		}
		if(flg) cout<<n+2*(n-ans)<<endl;
		else cout<<"-1\n";
	}
   return 0;
}
```

---

## 作者：Nightsky_Stars (赞：0)

# 思路：
贪心。

我们先找到与目标串单词匹配最多的字符串，用 $n$ 的代价把这个串直接复制上去，然后找到错误的单词，每次花费 $2$ 次代价替换成正确的，如果没有能匹配的正确的单词那么就无解。所以答案为：$n + (n-k)  \times 2$。

其中 $k$ 为最多匹配的单词数。

# CODE:


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=510;
string a[maxn],s[maxn][maxn];
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(0);
	#endif
	cin.tie(0);
	cout.tie(0);
	ll t;
	cin>>t;
	while(t--){
		bool vis[maxn]={0},flag=0;
		ll n,m,k=0;
		cin>>n>>m;
		for(ll i=1;i<=n;i++){
			cin>>a[i];
		}
		for(ll i=1;i<=m;i++){
			ll c=0;
			for(ll j=1;j<=n;j++){
				cin>>s[i][j];
				if(s[i][j]==a[j]) c++,vis[j]=1;
			}
			k=max(k,c);
		}
		for(ll i=1;i<=n;i++){//判断无解
			if(!vis[i]){
				flag=1;
				break;
			}
		}
		if(flag) cout<<"-1\n";
		else cout<<n+(n-k)*2<<"\n";
	}
	#ifndef ONLINE_JUDGE
	system("pause");
	#endif
	return 0;
}
```
[AC记录](https://codeforces.com/contest/2093/submission/317344531)

---


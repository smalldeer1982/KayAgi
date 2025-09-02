# String Reconstruction

## 题目描述

Ivan有一个只包含小写英文字母的字符串s。然而他的朋友Julia为了捉弄他藏起了字符串s。
相比起找回原来的字符串，Ivan更倾向于造一个新的。
 
Ivan知道一些有关于字符串s的信息。这意味着他记得字符串$t_{i}$在字符串s中至少出现了$k_{i}$次，以及$k_{i}$个$t_{i}$在s中出现的位置--$x_{i,1}$，$x_{i,2}$，$x_{i,3}$，$x_{i,4}$，…，$x_{i,k_{i}}$。他记得n个这样的字符串$t_{i}$。

 你要重建出一个符合Ivan记得的所有信息的字符串，如果有多个答案符合要求，取字典序最小的一个。字符串$t_{i}$只包含小写字母。

## 样例 #1

### 输入

```
3
a 4 1 3 5 7
ab 2 1 5
ca 1 4
```

### 输出

```
abacaba
```

## 样例 #2

### 输入

```
1
a 1 3
```

### 输出

```
aaa
```

## 样例 #3

### 输入

```
3
ab 1 1
aba 1 3
ab 2 3 5
```

### 输出

```
ababab
```

# 题解

## 作者：狸狸养的敏敏 (赞：5)

一道练并查集的好题= =话说我的翻译被拒了= =
每一个字符的爸爸都是他所在区间的爸爸，这样只要看看这个字符的爸爸有没有被处理过，就可以判断是否需要填充。（好吧说的有点玄学，语文0分别打我（逃））（纯模拟我敢保证你会爆）
代码如下，看不懂我的解释的看注释吧：
```cpp
#include<iostream>
#define N 2000002//最大长度
using namespace std;
int go[N];//父亲数组
string res="";//答案
int GO(int p) {//相当于getfather，加了个路径压缩，找爸爸awa
	if(go[p]==p)return p;
	return go[p]=GO(go[p]);//路径压缩
}
int main() {
	ios::sync_with_stdio(0); //玄学的关闭同步
	for(int i=0; i<N; ++i) {//初始化，因为要字典序最小所以全部设为a
		res+='a';
		go[i]=i;//一开始初始化成自己（自己各自为家）
	}
	int n;
	cin>>n;
	int mx=0;//字符串长度
	while(n--) {
		string s;
		cin>>s;
		int K;
		cin>>K;//S，K同题意
		int len=s.length();//取得要填充字符串的长度
		while(K--) {
			int pos;//位置
			cin>>pos;
			--pos;//字符串从0开始计算，所以位置-1
			mx=max(mx,pos+len);//长度
			for(int i=pos; i<pos+len;) {
				int P=GO(i);//找到字符i的爸爸,看看有没有填充过
				if(P>pos+len-1)break;//如果他的爸爸在外面（当前区间填充过），那就取消操作
				res[P]=s[P-pos];//字符赋值string类可以当char[]类用
				go[P]=P+1;//把P的爸爸赋值为他前面的那个字符(注意，是位置！)
				i=go[P];//寻找下一个爸爸= =
			}
		}
	}
	for(int i=0; i<mx; ++i)
		cout<<res[i];//输出
	return 0;
}
```
我说的有点滑稽，管理员哥哥给我过了吧awa


---

## 作者：Islauso (赞：2)

其实说实话，在看到这道题时，我并没有想到要用并查集做（虽然标签里写了），我觉得，这道题其实可以暴力。

当然并不是说每输入一个字符串的起始位置就开始暴力更改这个区间，这样肯定是会T的。

我所说的暴力呢，是说在每个区间开始的位置标记这个区间是第几个字符串，如果有多个，就取其中最长的一个（因为根据题目要求一定存在符合要求的字符串，所以最长的一定包含了短的），然后最后在输出的时候判断一下该输出哪个字符串就行了。

那么不属于任何一个区间的地方呢？直接输出`a`不就完了！还有什么小写字母字符串是比全是`a`的字符串的字典序还要小呢？

注意！在输出过程中，如果遇到这个区间还没输出完，又到了另外一个区间的开始位置时，一定要判断当前正在输出的这个字符串能否将遇到的这个区间的字符串完全包含！如果不能，就立马退出，再输出从这个位置开始的字符串。

思路还是很简单的，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,x,m,a[10000001];//a数组标记每个区间所对应的字符串的下标，这个数组一定要开大一点，否则会RE
string t[100001];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>t[i]>>k;
		for(int j=1;j<=k;j++)
		{
			scanf("%d",&x);
			if(t[a[x]].length()<t[i].length())//如果已有区间从x开始，则比较两字符串的长度
				a[x]=i;
			m=max(m,x);
		}
	}
	int i=1;
	while(i<=m)
	{
		if(!a[i])//如果当前点不属于任何一个区间，输出'a'
			printf("a");
		else
		{
			int j;
			for(j=0;j<t[a[i]].length();j++)//输出当前区间的字符串
			{
				if(t[a[i+j]].length()+j>t[a[i]].length())//如果遇到另一个区间的开始，且无法完全包含，则退出，因为a默认为0，所以即使不是另一个区间的开始也没有问题
					break;
				else
					printf("%c",t[a[i]][j]);
			}
			i+=j;
			continue;
		}
		i++;
	}
	return 0;
}
```

我谔谔

---

## 作者：Ryan_Adam (赞：0)

# CF827A String Reconstruction
## 分析
题目保证有解，所以假如两个子串重叠了，那重叠部分一定是一样的。

所以可以统计覆盖到每个位置的最长字符串，然后遍历每个位置输出即可。为了保证字典序最小，对于没有子串覆盖到的位置输出 $a$ 即可。需要注意的是有的位置可能会被覆盖多次，前面说了重叠部分一样，那在逐位输出的时候检测到有更长的串就直接 `break` 继续输出下一个串就行了。

**注意空间。**

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Raiden{
    const int N=1e6+5;
    string s[N];
    int cnt[10*N],lens=-1,n;
    signed work()
    {
        cin>>n;
        for(int i=1;i<=n;i++){
            int k;
            cin>>s[i]>>k;
            for(int j=1;j<=k;j++){
                int x;
                cin>>x; 
                if(s[cnt[x]].size()<s[i].size())cnt[x]=i;
                lens=max(lens,x);
            }
        }
        for(int i=1;i<=lens;i++){
            if(!cnt[i])cout<<'a';
            else{
                int j;
                for(j=0;j<s[cnt[i]].size();j++){
                    if(s[cnt[i+j]].size()+j>s[cnt[i]].size())break;
                    else cout<<s[cnt[i]][j];
                }
                i+=j-1;
            }
        }
        return 0;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：Ryan_Adam (赞：0)

# CF827A String Reconstruction
## 分析
题目保证有解，所以假如两个子串重叠了，那重叠部分一定是一样的。

所以可以统计覆盖到每个位置的最长字符串，然后遍历每个位置输出即可。为了保证字典序最小，对于没有子串覆盖到的位置输出 $a$ 即可。需要注意的是有的位置可能会被覆盖多次，前面说了重叠部分一样，那在逐位输出的时候检测到有更长的串就直接 `break` 继续输出下一个串就行了。

**注意空间。**

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Raiden{
    const int N=1e6+5;
    string s[N];
    int cnt[10*N],lens=-1,n;
    signed work()
    {
        cin>>n;
        for(int i=1;i<=n;i++){
            int k;
            cin>>s[i]>>k;
            for(int j=1;j<=k;j++){
                int x;
                cin>>x; 
                if(s[cnt[x]].size()<s[i].size())cnt[x]=i;
                lens=max(lens,x);
            }
        }
        for(int i=1;i<=lens;i++){
            if(!cnt[i])cout<<'a';
            else{
                int j;
                for(j=0;j<s[cnt[i]].size();j++){
                    if(s[cnt[i+j]].size()+j>s[cnt[i]].size())break;
                    else cout<<s[cnt[i]][j];
                }
                i+=j-1;
            }
        }
        return 0;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：OIer_ACMer (赞：0)

~~为什么一定要用树状数组呢？~~

# 题目解析：

本题，我们其实根本不用考虑要用树状数组来维护字符串这种比较复杂的类型，我们其实可以像莫队算法一样根据每一次位置区间来确定要添加的字符。

首先，我们定义 $mt_i$ 为第 $i$ 位之后第一个没有字符的地方，初始化所有的 $mt_i$ 都为 $i$，因为一开始所有位上都是空的。我们在面对每一个要求时利用每次的字符串长度得到 $l$ 和 $r$。

之后，我们在之后要考虑两种情况 。

如果 $mt_l$ 的值等于 $l$，那么，我们就可以直接填，毕竟 $l$ 后第一位空的就是 $l$，同时将 $mt_l$ 更新至 $mt_{r+1}$，**因为我们这一位已经填了，至于之后的话在此次循环就不会到这一位了**，我们要为之后填其他的字符做准备，而且，无论怎样，**这个位置往后数 $len$ 位要被此次输入的字符串填满**，将 $mt_l$ 更新至 $mt_{r+1}$ 是为了提前更新为下一次判断做准备。

至于 $mt_l$ 的值不等于 $l$，那么我们直接定一个中间变量 $q$ 将 $l$ 和 $mt_l$ 一并移动到后一位的值。你问我为什么不把此处原有的字符给替代掉，呵呵，其实，读题就可以发现我们所有的输入都不会互相矛盾，就是不会出现**输入的小字符串与其他该位置的大字符串不成子串关系**。

# 代码如下：

```

#include <bits/stdc++.h>
using namespace std;
int n;
int k;
int maxn = INT_MIN;
int x[1000009];
int mt[10000009];
char ans[10000009];
int main()
{
    cin >> n;
    for (int i = 1; i < 10000009; i++)
    {
        mt[i] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        char a[1000009];
        cin >> (a + 1) >> k;
        // cout << "k=" << k << endl;
        int len = strlen(a + 1);
        // cout << "len=" << len << endl;
        for (int j = 1; j <= k; j++)
        {
            cin >> x[j];
        }
        // for (int j = 1; j <= k; j++)
        // {
        //     cout << "x[" << i << "]=" << x[i] << endl;
        // }
        for (int j = 1; j <= k; j++)
        {
            int l = x[j], r = x[j] + len - 1;
            maxn = max(maxn, r);
            while (1)
            {
                // cout << "l=" << l << endl;
                if (l >= x[j] + len)
                {
                    break;
                }
                if (mt[l] == l)
                {
                    ans[l] = a[l - x[j] + 1];
                    mt[l] = mt[r + 1]; 
                    l++;
                }
                else
                {
                    int q = mt[l];
                    mt[l] = mt[q]; 
                    l = q;
                }
            }
        }
    }
    for (int i = 1; i <= maxn; i++)
    {
        if (mt[i] == i)
        {
            cout << 'a';
        }
        else
        {
            cout << ans[i];
        }
    }
    return 0;
}

```

---

## 作者：Durancer (赞：0)

#### 题目大意

给定一系列字串及它所在字符串中的位置，要求拼凑出符合题意且字典序最小的字符串

#### 思路分析

~~(暴力出奇迹)~~

一、首先我们可以知道的是，因为这是一定保证有解的，那么我们可以得到以下的性质

出现在同一个位置的子串，一定是相同的一个子串不一样长的一些部分，那么长度较大的一定会包含着长度较小的，所以我们此时就可以对比以下，然后把每个位置都更新成长度最大的

二、输入处理完后，在输出上也有一些小技巧

看一些特殊的情况

当找到一个位置没有字符串出现时，输出字典序最小的$a$

当找到一个位置有字符串出现时,此时会出现两种情况

1.在输出一个字符串的时候，在这其中的位置上出现了其他的字符串

上例子来解释一下

```
当前输出的字串 aabbcc
部分重合的字串    bccdd   

```
当我们输出到第四位的时候，出现了一个与他部分重叠的字串，那么我们现在要直接跳出该层循环，转移到下一层去

为什么呢，因为读题目可以知道的是，我们只知道这个字串的初始位置，并不知道这其中所有的位置标号，所以说，在每个位置所储存的字符串下标中，有一部分可能是$0$，但是包含在了字串当中，所以循环会直接出去略过去，并不会造成影响。

而当前这种情况，如果我们将当前输出的字串输出到了最后，那么出现的情况是下一个位置的标号是$0$，不能进行匹配，只好输出$a$，导致答案错误。

处理的时候只需要判断一下当前字符串$i$的长度是否小于已经输出了的长度$dis$+部分重合的字串$j$之和

符合弹出的条件为：

$$len_{i} < len_j+dis$$

#### 优化

别忘了用scanf，不然会T，QWQ

#### 代码实现

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
using namespace std;
const int N=1e7+9;
const int M=1e6+9;
int n;
int maxn;
string k[M];//用来存储每个字符串 
int a[N];//存储当前的位置是应用的哪一个字符串 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>k[i];
		cin>>x;
		for(int j=1;j<=x;j++)
		{
			int place;
			scanf("%d",&place); 
			if(k[a[place]].length()<k[i].length())
			a[place]=i;
			//如果该字符串的长度大于原来的字符串的长度
			//那么就说明以前的小字符串一定包含在当前的字符串里
			//那么就把位置更新一下 
			maxn=max(place,maxn);
		}
	}
	for(int i=1;i<=maxn;i++)
	{
		if(!a[i])//当前位置没有字符串，就输出字典序最小的
		{
			printf("a");
			continue;	
		}
		int j;
		for(j=0;j<k[a[i]].length();j++)
		{
			if(k[a[i+j]].length()+j>k[a[i]].length())
			//也就是说，在输出的时候遇到了另外的一个区间并且没有包含完全
			//那就不输出了
			break;
			else 
			{
				printf("%c",k[a[i]][j]); 
			}
		}
		i+=j;
		if(j!=0) i--;
	}
	return 0;
}
```


---

## 作者：Sakurajima_Mai (赞：0)

我只会线段树做法诶~



- 1. 首先呢

	很容易想到的是，所求是最小的符合要求的字符串，动动脑子都知道，没有比全都是$a$还要小的子串了，
    
    因此呢，我们干脆全赋成$a$算了，然后再根据题意进行修改，这样的话，很显然的，最小的要求我们就已经满足了。
   
- 2. 接着

  一个一个的改的话，超时是肯定的(当然，将大佬排除在外)，那么我们考虑维护一颗线段树。
  
- 3. 然后嘞

	线段树中维护两个参数，一个是我们的访问数组$visit$,另一个就是我们的子串值$ans$.
    
- 4.最后，

	那就根据要求改呗~
    
Code:
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lson l,mid,id<<1
#define rson mid+1,r,id<<1|1

const ll MOD = 1000000007;
 
char ans[2000005];
int vis[8000005];
string s;
void add(int l, int r, int id, int L, int R) {
	if (vis[id] == r - l + 1)return;
	if (l == r) {
		ans[l] = s[l - L];
		vis[id] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	if (R <= mid)add(lson, L, R);
	else if (L > mid)add(rson, L, R);
	else{
		add(lson, L, R);
		add(rson, L, R);
	}
	vis[id] = vis[id << 1] + vis[id << 1 | 1];
}
int main(){
	freopen("CF827A.in","r",stdin);
	freopen("CF827A.out","w",stdout);
	memset(vis, 0, sizeof(vis));
	int n, x, maxx = 0; scanf("%d", &n);
	for (int i = 0; i <= 2000000; ++i)ans[i] = 'A';
	for (int i = 0; i < n; ++i) {
		cin >> s;
		int t; scanf("%d", &t);
		int len = s.size();
		while (t--) {
			scanf("%d", &x); maxx = max(maxx, x + len - 1);
			add(1, 2000000, 1, x, x + len - 1);
		}
	}
	for (int i = 1; i <= maxx; ++i) {
		if (ans[i] == 'A')printf("a");
		else printf("%c", ans[i]);
	}	
	return 0;
}
```

---


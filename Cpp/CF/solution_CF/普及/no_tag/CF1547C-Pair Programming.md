# Pair Programming

## 题目描述

Monocarp and Polycarp are learning new programming techniques. Now they decided to try pair programming.

It's known that they have worked together on the same file for $ n + m $ minutes. Every minute exactly one of them made one change to the file. Before they started, there were already $ k $ lines written in the file.

Every minute exactly one of them does one of two actions: adds a new line to the end of the file or changes one of its lines.

Monocarp worked in total for $ n $ minutes and performed the sequence of actions $ [a_1, a_2, \dots, a_n] $ . If $ a_i = 0 $ , then he adds a new line to the end of the file. If $ a_i > 0 $ , then he changes the line with the number $ a_i $ . Monocarp performed actions strictly in this order: $ a_1 $ , then $ a_2 $ , ..., $ a_n $ .

Polycarp worked in total for $ m $ minutes and performed the sequence of actions $ [b_1, b_2, \dots, b_m] $ . If $ b_j = 0 $ , then he adds a new line to the end of the file. If $ b_j > 0 $ , then he changes the line with the number $ b_j $ . Polycarp performed actions strictly in this order: $ b_1 $ , then $ b_2 $ , ..., $ b_m $ .

Restore their common sequence of actions of length $ n + m $ such that all actions would be correct — there should be no changes to lines that do not yet exist. Keep in mind that in the common sequence Monocarp's actions should form the subsequence $ [a_1, a_2, \dots, a_n] $ and Polycarp's — subsequence $ [b_1, b_2, \dots, b_m] $ . They can replace each other at the computer any number of times.

Let's look at an example. Suppose $ k = 3 $ . Monocarp first changed the line with the number $ 2 $ and then added a new line (thus, $ n = 2, \: a = [2, 0] $ ). Polycarp first added a new line and then changed the line with the number $ 5 $ (thus, $ m = 2, \: b = [0, 5] $ ).

Since the initial length of the file was $ 3 $ , in order for Polycarp to change line number $ 5 $ two new lines must be added beforehand. Examples of correct sequences of changes, in this case, would be $ [0, 2, 0, 5] $ and $ [2, 0, 0, 5] $ . Changes $ [0, 0, 5, 2] $ (wrong order of actions) and $ [0, 5, 2, 0] $ (line $ 5 $ cannot be edited yet) are not correct.

## 样例 #1

### 输入

```
5

3 2 2
2 0
0 5

4 3 2
2 0 5
0 6

0 2 2
1 0
2 3

5 4 4
6 0 8 0
0 7 0 9

5 4 1
8 7 8 0
0```

### 输出

```
2 0 0 5 
0 2 0 6 5 
-1
0 6 0 7 0 8 0 9
-1```

# 题解

## 作者：SunsetLake (赞：3)

## 思路
题意这里就不讲了，直接进入正题。

贪心。

首先我们知道要想尽可能的让每一次操作都合法就得使 $k$ 最大化，那么要使 $k$ 最大就得尽可能的选择 $0$ 操作，所以贪心策略就出来了:优先选择 $0$ 操作，$A,B$ 序列那个有 $0$ 就选哪个合并。如果两个序列当前都没有 $0$，就需要进行判断了：

------------
- 如果 $k$ 比 $A$ 序列当前的数和 $B$ 序列当前的数都小一定无解(想想为什么)。
- 否则在 $A,B$ 序列当前的中选择比 $k$ 小的进行合并。


------------
其余细节将在注释中呈现。

## 代码
	 
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[105],b[105],c[205];//c数组表示合并后序列
int k,m,n;
bool ok;
int main(){
	cin>>t;
	while(t--){
		int cnt=0;
		ok=0;
		scanf("%d%d%d",&k,&n,&m);
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=m;++i){
			scanf("%d",&b[i]);
		}
		a[n+1]=b[m+1]=0x3f3f3f3f;//赋为极大值防止在合并时将多余的0加入序列
		int l=1,r=1;//l,r分别表示A序列和B序列当前数的位置
		while(l<=n||r<=m){
			if(a[l]==0){
				c[++cnt]=0;
				l++;
				k++;
			}
			else if(b[r]==0){
				c[++cnt]=0;
				r++;
				k++;
			}//贪心的合并两序列
			else{
				if(k<a[l]&&k<b[r]){//如果k比A,B序列当前数都小即无解
					puts("-1");
					ok=1;
					break;
				}
				if(k>=a[l])c[++cnt]=a[l],l++;//否则正常合并
				else if(k>=b[r])c[++cnt]=b[r],r++;
			}
		}
		if(!ok){
			for(int i=1;i<=cnt;++i)cout<<c[i]<<" ";
			puts("");
		}
	}
	return 0;
}

```
完结撒花~~。

---

## 作者：xuanyuan_Niubi (赞：2)

# 题目大意：

有 $ T $ 组测试数据，每组测试数据给定 $ k $，$ n $，$ m $，和长度为 $ n $ 的数组 $ a_i $ 和长度为 $ m $ 的数组 $ b_i $。

$ k $ 是你拥有的值，每次操作，你可以任意从两个数组的第一个数中选一个进行操作：

- 如果是 $ 0 $，那么 $ k+1 $。
- 如果不是 $ 0 $ 但是 $ \le k $，就可以进行一次什么都不用做的操作。
- 如果不是 $ 0 $ 并且 $ > k $，那么就不可以进行操作。

每次操作后都要把你选出的那个数删掉。求可能的一个操作的顺序。

若无法将两个数组中的所有数选完，则输出“-1”。

# 分析：

很容易想到，如果两个数组的第一个数都 $ >k $，就再也操作不了了。

如果其中一个数组是空的另一个数组的第一个数 $ >k $，也操作不了了。

所有就直接模拟就可以了，模拟选择数操作的过程。

我们可以先认准了一个数组，如果这个数组可以操作的话就一直操作下去，操作不了了就操作另外一个数组。然后重复直到两个数组为空，中间过程如果发现两个数组都操作不了了那就不行了。

为什么可以这样呢？如果我选 $ a_1 $ 后可以选择 $ b_1 $ 进行操作，那么我将 $ a_2 $ 操作了后（如果 $ a_2 $ 可以操作的话）$ k $ 的值可能会更大，但一定不会变小。所以先操作 $ a_2 $ 再操作 $ b_1 $ 是完全可行的。

# 代码：

```cpp
#include<stack>
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int M=2e5+5;
inline int read(){
	char c=getchar();int x=0,f=1;
	for(;c<'0'||c>'9';c=getchar())if(c=='-')f=0;
	for(;c<='9'&&c>='0';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return f?x:-x;
}
inline int abs(int x){return x>0?x:-x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
inline void swap(int &a,int &b){a^=b^=a^=b;}
queue<int>a,b,c;
int main(){
	int T=read();
	while(T--){
		int k=read(),n=read(),m=read();
		bool fl=1;
		for(int i=1;i<=n;i++){
			int x=read();a.push(x);//将a、b存到队列里面更容易进行将头删去的操作
		}
		for(int i=1;i<=m;i++){
			int x=read();b.push(x);
		}
		while(!a.empty()||!b.empty()){
			if((a.front()>k&&b.front()>k)||(b.empty()&&a.front()>k)||(a.empty()&&b.front()>k)){//如果发现操作不了了就不操作了，标记一下。
				fl=0;break;
			}
			int x=a.front();
			while(x<=k&&!a.empty()){//对a操作一直到a操作不了了为止
				if(x==0)k++;
				c.push(x);a.pop();x=a.front(); 
			}
			x=b.front();
			while(x<=k&&!b.empty()){//对b操作一直到b操作不来了为止
				if(x==0)k++;
				c.push(x);b.pop();x=b.front();
			}
		}
		if(!fl)printf("-1");
		else{
			while(!c.empty()){
				int x=c.front();c.pop();
				printf("%d ",x);
			}
		}
		puts("");
		while(!c.empty())c.pop();//最后一定要全部都清空
		while(!a.empty())a.pop();
		while(!b.empty())b.pop();
	}
	return 0;
}
```



---

## 作者：dalao_see_me (赞：1)

## 题目大意
初始有 $k$ 行，有两个操作序列 $a,b$，你需要合并它们，需要保证原来的相对顺序，若操作给的数字为 $0$ 则增加一行，否则为修改数字指向的那行，你需要给出合并的序列，使得任何修改的行都存在。若没有则输出 `-1`。
## 做法
贪心。

在保证相对顺序的情况下显然能增加行数就增加，如果不行就看能否修改。然后用两个变量慢慢推进就好了。

上代码。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int _;
int a[N], b[N], c[N];
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') f = -f; c = getchar();}
	while (c >= '0' && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}
	return x * f;
}
int main() {
	_ = read();
	while (_--) {
		int len = read(), n = read(), m = read(), tot = 0;
		for (int i = 1; i <= n; i++) a[i] = read();
		for (int j = 1; j <= m; j++) b[j] = read();
		int i = 1, j = 1, f = 1;
		while (i <= n && j <= m && f) {
			if (a[i] == 0) {
				c[++tot] = 0;
				i++; len++;
				continue;
			}
			if (b[j] == 0) {
				c[++tot] = 0;
				j++; len++;
				continue;
			}
			if (a[i] <= len) {
				c[++tot] = a[i];
				i++;
				continue;
			}
			if (b[j] <= len) {
				c[++tot] = b[j];
				j++;
				continue;
			}
			f = 0;
		}
		if (!f) {
			puts("-1");
			continue;
		}
		while (i <= n && f) {
			if (a[i] == 0) {
				c[++tot] = 0;
				i++; len++;
				continue;
			}
			if (a[i] <= len) {
				c[++tot] = a[i];
				i++;
				continue;
			}
			f = 0;
		}
		while (j <= m && f) {
			if (b[j] == 0) {
				c[++tot] = 0;
				j++; len++;
				continue;
			}
			if (b[j] <= len) {
				c[++tot] = b[j];
				j++;
				continue;
			}
			f = 0;
		}
		if (f) {
			for (i = 1; i <= tot; i++) printf("%d ", c[i]);
			puts("");
		}
		else puts("-1");
	}
	return 0;
}
```

---

## 作者：XBaiC (赞：0)

贪心题。

### 思路

在两个数合并的时候让短期利益最大化，也就是贪心。

我们分情况讨论：

1. $a>k$ 且 $b>k$，则停止合并并输出 `-1`。

2. $a=0$ 或 $b=0$，则 $k+1$ 并继续。

3. $a\leq k$ 或 $b \leq k$，则直接继续下一轮。

CODE 较为简单，这里就不放了。

---

## 作者：PLDIS (赞：0)

贪心。我们先开一个答案序列。显然，一开始两个序列里有 $0$ 就肯定先用上（但是要保证顺序，不能先用中间的再用前面的），从原先数组删除，插入答案序列，因为我们想要让行数越大越好，才能应对后面的数。如果都没有 $0$，那么就**选更小的插入**，因为这样才能保证成功的几率最大。如果最小的数都超过了现有的行数，那么这就说明**不可能通过任何方法构造出合法的序列**，我们就输出 `-1`。最后，如果两个序列都空了并且没有输出 `-1`，我们就输出答案序列。

我们可以设两个数 $i$ 和 $j$，分别代表第一个序列和第二个序列分别已经删到哪里了。当 $i$ 和 $j$ 都走到数组的尽头时，就代表它们已经删空了。

AC 代码：


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int t;
    cin >> t;
    while(t--){
        int k, n, m;
        cin >> k >> n >> m;
        int a[n + 1], b[m + 1];
        for(int i = 0;i < n;i++){
            cin >> a[i];
        }
        for(int i = 0;i < m;i++){
            cin >> b[i];
        }
        a[n] = 0x3f3f3f3f, b[m] = 0x3f3f3f3f;
        vector<int> ans; //答案序列
        int l = k, ai = 0, bi = 0; //ai，bi分别表示两个数组分别删到了哪里，l为行数
        bool flag = false;
        while(ans.size() < n + m){
            if(a[ai] == 0){
                ai++, ans.push_back(0);
                l++;
                continue;
            }
            else if(b[bi] == 0){
                bi++, ans.push_back(0);
                l++;
                continue;
            }
            int p = min(a[ai], b[bi]);
            if(p == a[ai]){
                ai++;
            }
            else{
                bi++;
            }
            if(p > l){
                flag = true;
                break;
            }
            ans.push_back(p);
        }
        if(flag){
            cout << -1 << endl;
        }
        else{
            for(int i = 0;i < ans.size();i++){
                cout << ans[i] << " "; //输出答案序列
            }
            cout << endl;
        }
    }
    return 0;
}
```

---

## 作者：KSToki (赞：0)

# 题目大意
初始有 $k$ 行，给定两个操作序列 $a$ 和 $b$，你需要将它们合并为一个操作序列，需保证它在原数列中的相对位置不变。将操作序列依次操作，如果操作为 $0$ 则将 $k$ 加一，若不为 $0$ 且大于 $k$，则该序列不合法。问是否存在合法序列，如果有请给出一个。
# 题目分析
贪心。操作数越小越靠前越好，这样我们可以用类似归并排序的方式把 $a$ 和 $b$ 合并起来，意味着 $0$ 的机会更多。再依次暴力判断即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,k,n,m,a[101],b[101],ans[201];
int main()
{
	T=read();
	while(T--)
	{
		k=read();
		n=read();
		m=read();
		for(R int i=1;i<=n;++i)
			a[i]=read();
		for(R int i=1;i<=m;++i)
			b[i]=read();
		int i=1,j=1;
		ans[0]=0;
		while(i<=n&&j<=m)
		{
			if(a[i]<b[j])
			{
				if(k<a[i])
				{
					puts("-1");
					goto over;
				}
				if(a[i]==0)
					++k;
				ans[++ans[0]]=a[i];
				++i;
			}
			else
			{
				if(k<b[j])
				{
					puts("-1");
					goto over;
				}
				if(b[j]==0)
					++k;
				ans[++ans[0]]=b[j];
				++j;
			}
		}
		while(i<=n)
		{
			if(k<a[i])
			{
				puts("-1");
				goto over;
			}
			if(a[i]==0)
				++k;
			ans[++ans[0]]=a[i];
			++i;
		}
		while(j<=m)
		{
			if(k<b[j])
			{
				puts("-1");
				goto over;
			}
			if(b[j]==0)
				++k;
			ans[++ans[0]]=b[j];
			++j;
		}
		for(R int i=1;i<=ans[0];++i)
			printf("%d ",ans[i]);
		puts("");
		over:;
	}
	return 0;
}
```

---

## 作者：Mix66 (赞：0)

### 思路

在两个数合并的时候贪心。

讨论情况：

- 若 $a,b$ 都大于 $k$，停止合并输出 `-1`。

- 若 $a,b$ 有一个等于 $0$，让 $k+1$ 并继续。

- 若 $a$ 或 $b$ 有一个小于等于 $k$，直接继续下一轮。

---

## 作者：PikachuQAQ (赞：0)

## Description

[Link](https://www.luogu.com.cn/problem/CF1547C)

## Solution

其实是**贪心**题。

对于构造合法序列的“推入”和“删除”操作，私以为用队列模拟会更容易理解。

令 $c$ 为合法序列。

首先考虑无解：对于序列 $a$ 和 $b$，如果 $a_1,b_1>k$，或者 $a,b$ 其中之一为空，另一序列的第一项大于 $k$，那么情况无解。

然后进行合法序列构造。假设对非空合法 $a_i$ 进行构造，有如下过程：

- 如果 $a_1=0$，则 $k\leftarrow k+1$。
- 将 $a_1$ 推入 $c$，删除 $a_1$。

在最后判断 $c$ 的长度是否为 $a$ 和 $b$ 的长度和，如果不是说明无解，否则输出合法序列。

记得**多测不清空，亲人两行泪**。

## Code

```cpp
// 2023/6/28 Accept__

#include <iostream>

using namespace std;

const int kMaxN = 107;

int t, k, n, m;
queue<int> a, b, c;

void init() {
    while (a.size()) {
        a.pop();
    }
    while (b.size()) {
        b.pop();
    }
    while (c.size()) {
        c.pop();
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (cin >> t; t; t--) {
        init();
        cin >> k >> n >> m;
        for (int i = 1, x; i <= n; i++) {
            cin >> x;
            a.push(x);
        }
        for (int i = 1, x; i <= m; i++) {
            cin >> x;
            b.push(x);    
        }
        while (a.size() || b.size()) {
            if ((a.front() > k && b.front() > k) || (a.size() == 0 && b.front() > k) || (a.front() > k && b.size() == 0)) {
                break;
            }
            for (int i = a.front(); i <= k && a.size(); i = a.front()) {
                c.push(i), a.pop(), (i == 0) && (k++);
            }
            for (int i = b.front(); i <= k && b.size(); i = b.front()) {
                c.push(i), b.pop(), (i == 0) && (k++);
            }
        }
        if (n + m != c.size()) {
            cout << -1 << '\n';
        } else {
            for (int i = c.front(); c.size(); i = c.front()) {
                cout << i << ' ', c.pop();
            } cout << '\n';
        }
    }

    return 0;
}
```


---

## 作者：zbk233 (赞：0)

## 解题思路

这道题就是在两个数组合并的过程中加入贪心的思想。

- 若是 $a$ 数组与 $b$ 数组当前的数都大于 $k$，直接输出 ```-1``` 并退出合并。

- 若 $a$ 或 $b$ 数组当前的数为 $0$，$k+1$ 并进行下一轮。

- 若 $a$ 或 $b$ 数组当前的数小于或等于 $k$，不进行操作，直接进行下一轮。

## 参考代码

```cpp
#include<iostream>
using namespace std;
int a[105],b[105],ans[205];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t,k,n,m,lena,lenb,lenc,flag;
	cin>>t;
	while(t--){
		cin>>k>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=m;i++){
			cin>>b[i];
		}
		lena=1;lenb=1;lenc=0;flag=0;
		while(lena<=n&&lenb<=m){
			if(a[lena]>k&&b[lenb]>k){
				flag=1;
				break;
			}
			if(a[lena]==0&&lena<=n){
				ans[++lenc]=0;
				k++;
				lena++;
			}
			if(b[lenb]==0&&lenb<=m){
				ans[++lenc]=0;
				k++;
				lenb++;
			}
			if(a[lena]!=0&&a[lena]<=k&&lena<=n){
				ans[++lenc]=a[lena];
				lena++;
			}
			if(b[lenb]!=0&&b[lenb]<=k&&lenb<=m){
				ans[++lenc]=b[lenb];
				lenb++;
			}
		}
		if(flag){
			cout<<"-1\n";
			continue;
		}
		while(lena<=n){
			if(a[lena]>k){
				flag=1;
				break;
			}
			if(a[lena]==0){
				k++;
				ans[++lenc]=0;
			}
			if(a[lena]!=0&&a[lena]<=k){
				ans[++lenc]=a[lena];
			}
			lena++;
		}
		while(lenb<=m){
			if(b[lenb]>k){
				flag=1;
				break;
			}
			if(b[lenb]==0){
				k++;
				ans[++lenc]=0;
			}
			if(b[lenb]!=0&&b[lenb]<=k){
				ans[++lenc]=b[lenb];
			}
			lenb++;
		}
		if(flag){
			cout<<"-1\n";
			continue;
		}
		for(int i=1;i<=n+m;i++){
			cout<<ans[i]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：XL4453 (赞：0)

### 解题思路：

考虑贪心。

将两个操作序列看成两个队列，编排操作序列就变成了每一次从两个队列中选出一个头放到答案序列中。

可以发现，尽量增加行数，在可能的情况下进行更改，一定是最优的。

因为在行数增加后，条件限制不会影响到之前的已经可行的更改操作，而且可以使得一些原本不可行的操作变得可行。
而且，由于每一个序列的操作的顺序已经固定，到达某一个位置时这个位置之前的所有贡献是固定的，也就是不随操作顺序变化。由此得出，上述的贪心一定是正确的。


---
### 代码：
```cpp
#include<cstdio>
using namespace std;
int T,k,n,m,a[105],b[105],now1,now2,ans[205],cnt,flag;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&k,&n,&m);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=m;i++)scanf("%d",&b[i]);
		cnt=0;now1=now2=1;
		flag=0;
		while(now1<=n||now2<=m){
			flag=1;
			while(a[now1]==0&&now1<=n){ans[++cnt]=0;now1++;k++;flag=0;}
			while(b[now2]==0&&now2<=m){ans[++cnt]=0;now2++,k++;flag=0;}
			while(a[now1]<=k&&a[now1]!=0&&now1<=n){ans[++cnt]=a[now1];now1++;flag=0;}
			while(b[now2]<=k&&b[now2]!=0&&now2<=m){ans[++cnt]=b[now2];now2++;flag=0;}
			if(flag){printf("-1\n");break;}
		}
		if(flag==0){
			for(int i=1;i<=cnt;i++)
			printf("%d ",ans[i]);
			printf("\n");
		}
	}
	return 0;
}
```


---


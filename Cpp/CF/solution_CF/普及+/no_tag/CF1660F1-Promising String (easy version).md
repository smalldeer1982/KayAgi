# Promising String (easy version)

## 题目描述

简单版与困难版的区别只有数据范围不同。

我们将一个非空字符串称作平衡字符串当且仅当它有相同数量的加号和减号。举例：字符串“+--+”和“++-+--”是平衡的，字符串“+--”，“--”和“”是不平衡的。

我们将一个字符串称作有希望的字符串当且仅当这个字符串可以通过几次（可能为0次）以下的操作来变成平衡的字符串。

操作：
- 将两个相邻的减号换成一个加号

特别的，一个平衡的字符串是一个有希望的字符串，但不是所有有希望的字符串都是平衡的字符串。

举个例子，字符串“-+---”是有希望的，因为你可以将两个相邻的减号换成加号后得到一个平衡的字符串“-++-”，或者“-+-+”。

给定一个字符串 $s$ ， $s$ 的多少个非空子串是有希望的？每个有希望的非空子串在答案中的计数次数必须与在字符串$s$中出现的次数相同。

子串是字符串中一段连续的字符，举例，对于字符串“+-+”来说，它的子串有“+-”，“-+”，“+”，“+-+”（它本身也是它的子串）等一些其他子串，但“--”，“++”，“-++”不是它的子串。

## 样例 #1

### 输入

```
5
3
+-+
5
-+---
4
----
7
--+---+
6
+++---```

### 输出

```
2
4
2
7
4```

# 题解

## 作者：XL4453 (赞：5)

### $\text{Difficulty : 1700}$
---
### 解题思路：

题目的数据范围很小，考虑用一个 $O(n^2)$ 的算法解决问题。

能进行的置换操作其实是将 $-$ 减少两个，并将 $+$ 增加一个，这也就意味着将两者的差值减少 $3$。那么每一次统计出有多少的位置上可以进行这种操作（注意不要重复计算），然后直接比较即可。

注意当 $+$ 比 $-$ 多的时候不能进行操作。


---
### 代码：
```cpp
#include<cstdio>
using namespace std;
int T,n,a[3005],x,y,p,l,ans;
char c;
char get(){
	char c=getchar();
	while(c=='\n'||c==' '||c=='\r')c=getchar();
	return c;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			c=get();
			if(c=='+')a[i]=1;
			else a[i]=0;
		}
		ans=0;
		for(int i=1;i<=n;i++){
			x=0;y=0;p=0;l=i-1;
			for(int j=i;j<=n;j++){
				if(a[j]==1)x++;
				else y++;
				if(a[j]==0&&a[j-1]==0&&j-l>=2)p++;
				if((y-x>=0)&&(y-x)%3==0&&(y-x)/3<=p)ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```
---
### 对于 $\text{hard version}$ 的提示：

如果将上面程序中对于 $p$ 的判断删去（直接默认成立），再次提交，同样能通过。

例如 [$152802487$](https://codeforces.com/contest/1660/submission/152802487)。


---

## 作者：heyx0201 (赞：2)

# Promising String (easy version) 题解
[Promising String (easy version) 题目传送门](https://www.luogu.com.cn/problem/CF1660F1)
## 思路
求区间内 `+` 比 `-` 多的个数。考虑 $n \le 2000$，可以得出一个 $O(n^2)$ 的算法：两个指针枚举左端点和右端点，前缀和 $O(1)$ 求出区间内 `-` 比 `+` 多的个数。只能将 $2$ 个 `-` 换成 $1$ 个 `+`，而 $2 + 1 = 3$，所以只有 `-` 比 `+` 多的个数是 $3$ 的倍数这个子串才为平衡字符串。

## 时空复杂度分析
### 时间
前缀和 $O(n)$，枚举字串左右端点 $O(n^2)$，总时间 $O(n^2)$。
### 空间
前缀和数组 $O(n)$，总空间 $O(n)$。
## Accepted Code
**[Accepted Record](https://www.luogu.com.cn/record/124780852)**
```cpp
#include<iostream>

using namespace std;

const int MAXN = 3e3 + 10;

int t, n, sum[MAXN];
string s;

void Solve(){
  cin >> n >> s;
  sum[0] = s[0] == '-' ? 1 : -1;
  for (int i = 1; i < n; i++){
    sum[i] = sum[i - 1] + (s[i] == '-' ? 1 : -1);
  }
  long long ans = 0;
  for (int i = 0; i < n; i++){
    for (int j = i; j < n; j++){
      ans += (sum[j] - sum[i - 1] >= 0 && (sum[j] - sum[i - 1]) % 3 == 0);
    }
  }
  cout << ans << '\n';
}

int main(){
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：KemononeRou (赞：2)

为了方便下面令减号为 $0$，加号为 $1$。

考虑如何判断一个区间合法。

发现操作一次之后 $0$ 的个数会减少 $2$，$1$ 的个数会增加 $1$，变化量为 $3$。

同时还要有足够的操作次数使得 $0$ 和 $1$ 的个数相等。

因此一个区间合法有如下条件：

- $0$ 的数量不少于 $1$ 的数量。

- $0$ 与 $1$ 的数量之差是 $3$ 的倍数。

- $0$ 与 $1$ 的数量之差除以 $3$ 不多于不交的 $00$ 数量。

可以 $O(n)$ 预处理出前缀 $0/1$ 数量，前缀不交的 $00$ 数量。

因为 $n \leq 3000$ 所以可以 $O(n^2)$ 枚举所有区间然后 $O(1)$ 判断。

[Code](https://www.luogu.com.cn/paste/ajyo01az)

---

## 作者：Y_QWQ_Y (赞：1)

可能第一眼看到题面还不知道怎么做，但是看到数据范围应该就很好做了。

### 解题思路
通过一次操作，可以将减少两个 $\lceil$-$\rfloor$ 和一个 $\lceil$+$\rfloor$，每次将他们的数量之差减少 $3$。那么。对于一个区间，$\lceil$-$\rfloor$ 的数量比 $\lceil$+$\rfloor$ 的个数多 $3$ 的倍数，就一定可以通过操作变成平衡的字符串。

现在我们只需要 $\Theta(n^2)$ 的枚举字串即可。

### 代码部分
那么可以写出代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, s[3005], ans;
string c;
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	cin >> t;
	while (t --)
	{
		ans = 0;
		cin >> n >> c;
		for (int i = 0; i < n; ++ i)s[i + 1] = s[i] + (c[i] == '-' ? 1 : -1);
		for (int i = 1; i <= n; ++ i)for (int j = i; j <= n; ++ j)
		{
			int sum = s[j] - s[i - 1];
			ans += (sum >= 0 && sum % 3 == 0);
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Pig_py (赞：1)

题目大意：

给你一个字符串，包含加号和减号，可以将**两个相邻的减号替换成一个加号**，询问有多少个子串能通过这个操作使得减号数量与加号数量一样。

首先我们知道，一个符合条件的字符串减号数量不会小于加号数量。其次，减号比加号多出的部分一定要是三的倍数。因为两个减号换一个加号，所以三个减号可以互相抵消。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		char a[3005];
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		long long ans=0;
		for(int i=2;i<=n;i++){
			for(int j=1;j<i;j++){
				int cnt1=0,cnt2=0;//cnt1 表示加号数量，cnt2 表示减号数量
				for(int k=j;k<=i;k++){
					if(a[k]=='+')cnt1++;
					if(a[k]=='-')cnt2++;
				}
				if(cnt1<=cnt2){
					if((cnt2-cnt1)%3==0){
						ans++;
					}
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}    
```

然而这段代码超出时限了，我们考虑用优化。

对于一个下标 $s$,$cnt[s]$ 表示 $1$ 到 $s$ 中每遇到加号就加一、每遇到减号就减一最后的结果。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		char a[3005];
		int cnt[3005];
		for(int i=1;i<=n;i++){
			cin>>a[i];
			cnt[i]=cnt[i-1];
			if(a[i]=='+')cnt[i]++;
			else cnt[i]--;
		}
		long long ans=0;
		for(int i=2;i<=n;i++){
			for(int j=1;j<i;j++){
				int q=cnt[i]-cnt[j-1];
				if(q>=0){
					if(q%3==0){
						ans++;
					}
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}    
```



---

## 作者：tZEROちゃん (赞：1)

upd：补充了 `-` 不连续的情况。

_______

> 给你一个字符串 $s$，你可以将连续的两个 `-` 合并成一个 `+`，求多少子串在合并若干次后，可以使得 `+` 与 `-` 的个数相同。

设在一个子串中 `+` 的个数为 $A$，`-` 的个数为 $B$，进行 $t$ 次合并后 `+` 和 `-` 的个数相同。那么显然 $t$ 次合并后 `+` 的个数为 $A + t$，`-` 的个数为 $B - 2t$，所以 

$$ A + t = B - 2t $$

移项可得

$$ B - A = 3t $$

因为 $t \ge 0$，所以 $3t \ge 0$，所以 $B - A \ge 0$。

也就是说，在一个子串中，当 `-` 的个数减去 `+` 的次数是 $3$ 的倍数，且是非负数，那么就说明这个子串是可行的，所以直接枚举一下就做完了。

对于「`-` 不连续」情况的说明：如果 `-` 的个数减去 `+` 的次数是 $3$ 的倍数，而且没有连续的 `-`，不难发现他一定是 `+-+-+-...` 这样的，此时不难发现 `-` 和 `+` 的个数仍是相同的。

```cpp
void solve() {
  string s;
  int ans = 0;
  iocin >> s >> s;
  // cout << s << ' ';
  rep (i, 0, s.size() - 1) {
    int curr = 0;
    rep (j, i, s.size() - 1) {
      curr += (s[j] == '-' ? 1 : -1);
      if (curr >= 0 && curr % 3 == 0) {
        ++ans;
      }
    }
  }

  cout << ans << endl;
}
```

---

## 作者：BLuemoon_ (赞：0)

求一遍前缀......-比+多的个数。

只能将减换成加，$2+1=3$，所以只有减比加多的个数是 $3$ 的倍数时，子串为平衡串。

然后，$O(n^2)$ 双指针找子序列，用求前缀和的方法求出区间内减比加多的个数。只要这个数是三的倍数且是正整数，就满足条件。

### 复杂度分析

#### 时间

求前缀 $O(n)$，遍历字串 $O(n^2)$。

总时间复杂度为 $O(n^2)$。

#### 空间

前缀数组 $O(n)$。

总空间复杂度为 $O(n)$ 。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans,m[3005]; //m为前缀数组
string s;
int main()
{
    for(cin>>t;t;t--)
    {
        ans=0; //多测不清空，WA到见祖宗~~~
        cin>>n>>s;
        s=' '+s;
        for(int i=1;i<=n;i++)
            m[i]=m[i-1]+(s[i]=='-'?1:-1); //求前缀
        for(int l=1;l<n;l++)
        {
            for(int r=l+1;r<=n;r++)
            {
                int tmp=m[r]-m[l-1]; //子串中减比加多的个数
                if(tmp%3==0&&tmp>=0) //减必须比加多
                    ans++;
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：bitsetint (赞：0)

题目链接（[in luogu](https://www.luogu.com.cn/problem/CF1660F1) and [in codeforces](https://codeforces.com/problemset/problem/1746/E1) )

## 思路

求出 $a_i$ 表示从第 $1$ 个位置到第 $i$ 个位置中 `+` 的个数和 `-` 的个数之差。

那么就可以 $O(n^2)$ 枚举所有非空子串，如果它是 “ 有希望 ” 的，就将其计入答案。

可以先用DP统计出每个非空子串中最多能替换掉多少组两个相邻的 `-` 。

通过观察可以看出，每次替换可以使 `+` 的个数和 `-` 的个数之差减少 $3$，那么只要这个子串中 `-` 的个数与 `+` 的个数之差是正整数而且是三的倍数，而且将一定量的 `--` 替换成 `+` 之后能使这个字符串变成“平衡的”，那么这个子串是“有希望”的。

## 具体看代码:


```cpp
#include <bits/stdc++.h>
using namespace std;
int f[3010];
int a[3010];
int b[3010];
int v[3010];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		memset(f,0,sizeof(f));
		int n;
		scanf("%d",&n);
		string s;
		cin>>s;
		s=" "+s;
		for(int i=1;i<=n;i++){
			if(s[i]=='+'){
				a[i]=1;
			}else{
				a[i]=-1;
			}
			b[i]=a[i];
		}
		for(int i=1;i<=n;i++){
			a[i]+=a[i-1];
		}// 求出 + 的个数和 - 的个数之差。
		int ans=0;
		for(int i=1;i<=n;i++){
			memset(f,0,sizeof(f));
			memset(v,0,sizeof(v));
			for(int j=i+1;j<=n;j++){
				if(b[j]+b[j-1]==-2){
					f[j]=f[j-2]+1;
					v[j]=1;
				}else{
					f[j]=f[j-1];
				}
			}//统计出每个非空子串中最多能替换掉多少组两个相邻的 `-`
			for(int j=i+1;j<=n;j++){
				if(a[j]-a[i-1]<=0&&(a[j]-a[i-1])%3==0&&a[j]-a[i-1]+f[j]*3>=0){//判断是否“有希望”
					ans++;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Cocoly1990 (赞：0)

首先瞎几把猜结论，一个区间是有希望的，当且仅当区间内 **`+` 的数量减去 `-` 的数量是 3 的倍数且小于 0.**

浅浅的证明一下。

显然每次操作就是将两个 `-` 换成 `+`，所以三个 `-` 只要有两个是相连的，则必然可以自我抵消。

所以我们需要证明，如果 `-` 比 `+` 至少多两个，则至少有一对 `--`.

考虑反证，如果没有，必然是形如 `-+-+ ... -+` 这样的，那么 `+` 就不会比 `-` 多至少两个。

考虑如何维护这个结论，一个常见套路是利用前缀和，把 `-` 标记为 -1， `+` 标记为 1.

暴力枚举左右端点可以轻松做到 $\mathcal{O}\left(n^2\right)$.

---

## 作者：哈士奇憨憨 (赞：0)

## 题目大意
如果一个非空字符串包含相同数量的加号和减号，我们将其称为平衡的。如果字符串可以用一个加号替换两个相邻的减号的多次得到进行平衡，我们将称之为“有希望的字符串”。

给定的字符串 $s$ 中有多少个非空子字符串是有希望的？

多组数据。
## 思路
暴力枚举字符串 $s$ 中子串起始的位置和长度（或枚举字符串 $s$ 中子串起始的位置和终止的位置）即可。

时间复杂度 $O(n^2T)$
## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, ans;
string s;
int main() {
    cin >> t;
    while(t--) {
        ans = 0; 
        cin >> n >> s;
        for(int i = 0; i < n; i++) {//起始位置
            int f = 0, z = 0;
            for(int j = i; j < n; j++) {//长度
                if(s[j] == '+') z++;
                else f++;
                if((f >= z) && (f - z) % 3 == 0) ans++;//当f-z能被3整除时，其中减号变加号时，差为（f-2)-(z+1)也能被3整除。最后差必为0。
            }
        }
        cout << ans << endl;
    }
    return 0;
}

```

---


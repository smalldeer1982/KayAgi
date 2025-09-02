# Broken Queries

## 题目描述

你是一位魔法师，你的作品被一条龙摧毁了，于是你决心用一台神奇的范围追踪器来追捕这条龙。然而，那条龙似乎在捉弄你。

这是一个交互式问题。

有一个隐藏的二进制数组 $a$，长度为 $n$（$n$ 是 2 的幂），以及一个隐藏的整数 $k$（$2 \le k \le n - 1$）。数组 $a$ 中仅有一个元素是 1，其余元素都是 0。对于两个整数 $l$ 和 $r$（$1 \le l \le r \le n$），定义区间和为 $s(l, r) = a_l + a_{l+1} + \cdots + a_r$。

你持有一个魔法装置，它能接收区间并返回区间和，但如果区间的长度至少是 $k$，则装置返回结果的相反值。具体来说，每次你可以提交一对整数 $[l, r]$ 进行查询（$1 \le l \le r \le n$），装置会按照下述规则返回 0 或 1：

- 如果 $r - l + 1 < k$，则返回 $s(l, r)$ 的实际值。
- 如果 $r - l + 1 \ge k$，则返回 $1 - s(l, r)$。

你需要用不超过 33 次查询找到隐藏的 $k$。

请注意，这个装置对于不同的测试用例始终固定不变，即隐藏的数组 $a$ 和整数 $k$ 在游戏开始前就已经确定，并在整个过程中不变。

## 说明/提示

在第一个测试用例中，给出隐藏整数 $k = 6$ 且数组中唯一的 1 位于索引 6 上，因此数组 $a = [0, 0, 0, 0, 0, 1, 0, 0]$。

- 对于查询 (3, 5)，因为 $5 - 3 + 1 = 3 < k$，装置返回实际结果。因为 6 不在区间 $\[3, 5\]$ 内，返回 0。
- 对于查询 (1, 8)，因为 $8 - 1 + 1 = 8 \ge k$，装置返回相反结果，返回 0。
- 对于查询 (4, 8)，因为 $8 - 4 + 1 = 5 < k$，装置返回实际结果，返回 1。
- 对于查询 (3, 8)，因为 $8 - 3 + 1 = 6 \ge k$，装置返回相反结果，返回 0。

示例解决方案输出 $k=6$，这也是正确的答案。

在第二个测试用例中，$k = 2$，数组中的 1 位于索引 3，因此 $a = [0, 0, 1, 0]$。

注意，示例解决方案在某些情况下可能无法充分确定 $k$，这仅仅是作为示例来提供参考。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
8

0

0

1

0

4

1

0```

### 输出

```
? 3 5

? 1 8

? 4 8

? 3 8

! 6

? 3 3

? 3 4

! 2```

# 题解

## 作者：ARIS2_0 (赞：5)

### 思路

大力分讨。

下文称对区间 $[l,r]$ 进行询问得到的值称为区间 $[l,r]$ 的检验值。

设 $mid_1=\frac{n}{2},mid_2=\frac{mid_1}{2}$。

考虑将数组分为 $3$ 部分：第一部分为 $[1,mid_2]$，第二部分为 $[mid_2+1,mid_1]$，第三部分为 $[mid_1+1,n]$。

设第 $i$ 个部分的检验值为 $val_i$。

接下来进行分类讨论：

> $val_1=val_2$，此时 $1$ 在第三部分内。
>
> 若 $val_3=1$，说明 $k>n-mid_1$，那么在 $[1,mid_1]$ 中找到一个最大的 $g$ 使得区间 $[g,n]$ 的检验值为 $0$，此时 $k=n-g+1$。
>
> 否则，在 $[1,mid_1]$ 中找到一个最小的 $g$ 使得区间 $[1,g]$ 的检验值为 $1$，此时 $k=g$。

> $val_1\not=val_2$，此时 $1$ 不在第三部分内。
>
> 若 $val_3=0$，说明 $k>n-mid_1$，那么在 $[mid_1+1,n]$ 中找到一个最小的 $g$ 使得区间 $[1,g]$ 的检验值为 $0$，此时 $k=g$。
>
> 否则，在 $[mid_1+1,n]$ 中找到一个最大的 $g$ 使得区间 $[g,n]$ 的检验值为 $1$，此时 $k=n-g+1$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define debug1(x) cerr<<#x<<"="<<x<<" "
#define debug2(x) cerr<<#x<<"="<<x<<"\n"
const int inf=1e16;
int check(int l,int r){
    cout<<"? "<<l<<" "<<r<<endl;
    int pos;cin>>pos;
    return pos;
}
signed main(){
	// ios::sync_with_stdio(0);
	// cin.tie(0);
	int t;cin>>t;
    while(t--){
        int n;cin>>n;
        int mid1=n/2,mid2=mid1/2;
        int val1=check(1,mid2),val2=check(mid2+1,mid1),val3=check(mid1+1,n);
        int g=0,l=0,r=0,k=0;
        if(val1==val2){
            l=1;r=mid1;
            if(val3){
                while(l<=r){
                    int mid=(l+r)/2;
                    if(check(mid,n)==0)g=mid,l=mid+1;
                    else r=mid-1;
                }
                k=n-g+1;
            }
            else{
                while(l<=r){
                    int mid=(l+r)/2;
                    if(check(1,mid)==1)g=mid,r=mid-1;
                    else l=mid+1;
                }
                k=g;
            }
        }
        else{
            l=mid1+1;r=n;
            if(val3){
                while(l<=r){
                    int mid=(l+r)/2;
                    if(check(mid,n)==1)g=mid,l=mid+1;
                    else r=mid-1;
                }
                k=n-g+1;
            }
            else{
                while(l<=r){
                    int mid=(l+r)/2;
                    if(check(1,mid)==0)g=mid,r=mid-1;
                    else l=mid+1;
                }
                k=g;
            }
        }
        cout<<"! "<<k<<endl;
    }
	return 0;
}
```

---

## 作者：freoepn (赞：3)

先对 $k$ 是否大于等于 $\frac{n}{2}$ 进行判断，首先询问 $[1,\frac{n}{4}]$ 和 $[\frac{n}{4}+1,\frac{n}{2}]$ ，如果两询问答案相同，说明 $1$ 在 $[\frac{n}{2}+1,n]$ 中，否则 $1$ 在 $[1,\frac{n}{2}]$ 中，询问判断 $1$ 所在区间就能得知 $k$ 是否大于等于 $\frac{n}{2}$。

若  $k$ 大于等于 $\frac{n}{2}$ 且 $[1,\frac{n}{2}]$ 中有 $1$ , 二分找到使询问 $[1,x]$ 为 $0$ 的最大 $x$ 即可。若  $k$ 大于等于 $\frac{n}{2}$ 且 $[1,\frac{n}{2}]$ 中有 $1$ ，同理二分找到使询问 $[x,n]$ 为 $0$ 的最小 $x$ 即可。若 $k$ 小于 $\frac{n}{2}$ ，用同样的方法在没有 $1$ 的区间中找 $0$ 即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
int query(int l, int r) {
  cout << "? " << l << " " << r << '\n';
  cout.flush();
  int x;
  cin >> x;
  return x;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    if (query(1, n / 4) != query(n / 4 + 1, n / 2)) {
      if (query(1, n / 2)) {
        int l = n / 2 + 1, r = n;
        while (l <= r) {
          int mid = (l + r) / 2;
          if (!query(1, mid)) {
            r = mid - 1;
          } else {
            l = mid + 1;
          }
        }
        cout << "! " << r + 1 << '\n';
        cout.flush();
      } else {
        int l = n / 2 + 1, r = n;
        while (l <= r) {
          int mid = (l + r) / 2;
          if (!query(n/2+1, mid)) {
            l = mid + 1;
          } else {
            r = mid - 1;
          }
        }
        cout << "! " << l -n/2 << '\n';
        cout.flush();
      }
    } else {
      if (query(n / 2 + 1, n)) {
        int l = 1, r = n / 2;
        while (l <= r) {
          int mid = (l + r) / 2;
          if (!query(mid, n)) {
            l = mid + 1;
          } else {
            r = mid - 1;
          }
        }
        cout << "! " << n - (l - 1) + 1 << '\n';
        cout.flush();
      } else {
        int l = 1, r = n / 2;
        while (l <= r) {
          int mid = (l + r) / 2;
          if (!query(mid, n/2)) {
            r = mid - 1;
          } else {
            l = mid + 1;
          }
        }
        cout << "! " << n/2 - (r ) + 1  <<'\n';
        cout.flush();
      }
    }
  }
  return 0;
}
```

---

## 作者：kevinZ99 (赞：2)

# solution

看到 $n=2^{m}$ 且 $m$ 为整数，刻在 DNA 里的反应告诉我们可以二分，所以我们考虑如何二分。

首先对于 $33$ 这个数字因为 $2^{30}$ 次方二分出来需要 $30$ 次，那么我们就需要在 $33-30=3$ 次之内判断一个可信任的区间，即判断一个区间一定有 $1$，或一定没有 $1$。

所以我们肯定考虑以 $\frac{n}{2}$ 作为分界点，显然的对于两个长度同为 $x$ 的区间来说，若两个区间系统返回的答案不同时，两区间中必内必有一个内有 $1$，因此可以在两次内判断出 $\left[ 1,\frac{n}{2}\right ]$ 内有没有 $1$，由于只有一个 $1$ 所以也可以得到 $\left[ \frac{n}{2}+1,n \right]$ 的 $1$ 的个数。

但是我们会发现，现在仍不能二分，因为我们虽然知道了 $1$ 的位置，但是并不知道k的大小不能确定二分的判断条件是系统返回 $0$ 还是 $1$，所以我们需要确定 $k$ 的大小，显然我们只能在 $1$ 次询问之内判断出来 $k$ 与 $\frac{n}{2}$ 的关系，由于前面我们知道了 $1$ 的位置，且刚刚好是以 $\frac{n}{2}$ 的长度的，所以我们考虑询问有 $1$ 的那个区间内若返回 $0$ 则 $k < \frac{n}{2}$ 否则大于 $\frac{n}{2}$。

然后我们就可以分四类进行讨论即可。

# code

```cpp
//Author:Kevin Z K Y
#include <bits/stdc++.h>
#define up(a,b,c) for(int (a)=(b);(a)<=(c);(a)++)
#define dn(a,b,c) for(int (a)=(b);(a)>=(c);(a)--)
#define fst first
#define sed second
using namespace std;
using ull = unsigned long long ;using ui = unsigned int ;
using ll = long long ;using hint = __int128 ;
using pii = pair<int,int> ;using pll = pair<ll,ll> ;
using vi = vector<int> ;using vl = vector<ll> ;
using vpi = vector<pii> ;using vpl = vector<pll> ;
using db = double ;namespace mystl{
	#define gc() getchar()
	ll qpow(ll a,ll b,const ll&p){if (a==0ll) return 0ll; ll c=1ll;
		while(b) { if(b & 1) c=a*c%p; a=a*a%p; b>>=1; } return c; }
	template<typename T>void read(T&x) {x=0; bool f=false; char ch;
		ch = gc(); while(ch<'0'||ch>'9') f |= ( ch=='-') , ch=gc();
		while(ch>='0'&&ch<='9') x=x*10+ch-'0' , ch=gc(); x=f?-x:x;}
	template<typename T>void write(T x){char s[40];short d=0;T y=x;
		if(x<0) putchar('-'),y=-y;if(x==0){ putchar('0'); return; }
		while(y){s[++d]=y%10+'0';y/=10;}while(d>0)putchar(s[d--]);}
	template<typename T>void wris(T x,char c){write(x);putchar(c);}
}using namespace mystl;
namespace my{
	void solve(){
		int n;cin>>n;
		cout<<"? "<<1<<' '<<n/4<<'\n';
		fflush(stdout);
		int ll;cin>>ll;
		cout<<"? "<<n/4+1<<' '<<n/2<<'\n';
		fflush(stdout);
		int lr;cin>>lr;
		if(ll==lr)cout<<"? "<<n/2+1<<' '<<n<<'\n';
		else cout<<"? "<<1<<' '<<n/2<<'\n';
		fflush(stdout);
		int P;cin>>P;
		int best;
		if(ll==lr){
			if(P){
//				cout<<"----------------1\n";
				int l=1,r=n/2;best=n/2;while(l<=r){
					int mid=l+(r-l)/2;
					cout<<"? "<<mid<<' '<<n<<'\n';fflush(stdout);
					int Flag;cin>>Flag;
					if(Flag==1)best=n-mid+1,r=mid-1;
					else l=mid+1;
				}
			}else {
//				cout<<"----------------2\n";
				int l=1,r=n/2;best=1;while(l<=r){
					int mid=l+(r-l)/2;
					cout<<"? "<<1<<' '<<mid<<'\n';fflush(stdout);
					int Flag;cin>>Flag;
					if(Flag==0)best=mid,l=mid+1;
					else r=mid-1;
				}
			}
		}else {
			if(P){
//				cout<<"----------------3\n";
				int l=n/2+1,r=n;best=n/2;while(l<=r){
					int mid=l+(r-l)/2;
					cout<<"? "<<1<<' '<<mid<<'\n';fflush(stdout);
					int Flag;cin>>Flag;
					if(Flag==1)best=mid,l=mid+1;
					else r=mid-1;
				}
			}else {
//				cout<<"----------------4\n";
				int l=n/2+1,r=n;best=1;while(l<=r){
					int mid=l+(r-l)/2;
					cout<<"? "<<mid<<' '<<n<<'\n';fflush(stdout);
					int Flag;cin>>Flag;
					if(Flag==0)best=n-mid+1,r=mid-1;
					else l=mid+1;
				}
			}
		}cout<<"! "<<best+1<<'\n';fflush(stdout);
	}
}
int main(){
//  freopen("","r",stdin);
//  freopen("","w",stdout);
//	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	int _=1;cin>>_;while(_--)my::solve();return 0;
}
```

---

## 作者：Priestess_SLG (赞：1)

感觉这题很聪明，赛时切这题的人是怎么想到的（

考虑分类 $1$ 的位置：若确定 $1$ 在序列左半边还是右半边，则必然能找出长度 $\le\frac{n}{2}$ 的区间使得该区间正确的和为 $0$，长度 $>\frac{n}{2}$ 的区间使得该区间正确的和为 $1$，这个时候直接简单二分即可。问题在于确定 $1$ 在左边还是右边。

考虑询问区间 $[1,\frac{n}{4}]$ 和 $[\frac{n}{4}+1,\frac{n}{2}]$。有一个关键性质：两个区间的长度相同，要么都说谎要么都不说谎。此时继续分类讨论：若两次询问出的结果不同，则显然两个区间中必然有恰好一个实际值为 $1$，即 $1$ 在序列的左半边，否则两个区间的实际值都必须为 $0$，即 $1$ 在序列的右半边。于是就做完了。[代码](https://codeforces.com/contest/2049/submission/297593649)。

---

## 作者：MrPython (赞：0)

神秘小分讨。输在了不知道二分应不应该 $+1$ 上。

本文 0 index，左闭右开。方便起见，我们将题目描述改为：每次询问那个 $1$ 是否在询问区间中，倘若询问区间长度大于等于 $k$ 则回答者会撒谎。

我们假设有 $k<\dfrac{n}{2}$。第一次，我们询问区间 $[0,\dfrac{n}{2})$，那这一次他会撒谎，询问结果为 true 则说明那个 $1$ 在右半区间，否则在左半中。我们可以直接前往不存在那个 $1$ 的区间二分。

再假设 $k\ge\dfrac{n}{2}$，则第一次询问结果为 true 则说明那个 $1$ 在左半区间，否则在右半区间中。如果 $1$ 在左半区间，那么我们可以每次询问都覆盖住左半区间，每次以询问 $[0,mid)$ 的形式二分。否则，我们每次询问都覆盖住右半区间，每次以询问 $[mid,n)$ 的形式二分。

如何区分这两者？我们先假设 $k<\dfrac{n}{2}$，并前往了那个没有 $1$ 的区间。我们再将这个区间砍成两半并分别询问，倘若 $1$ 确实不在这个区间里，两次询问的回答应该相同，否则说明我们去了有 $1$ 的区间，进而说明 $k\ge\dfrac{n}{2}$。

---


# [ABC326F] Robot Rotation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc326/tasks/abc326_f

右向きを $ x $ 軸正方向、上向きを $ y $ 軸正方向とする座標平面の原点にロボットがいます。ロボットは最初、$ x $ 軸正方向を向いています。

$ i=1,\ldots,N $ の順に以下の操作を行います：

- ロボットを右回りまたは左回りに $ 90 $ 度回転させる。その後、ロボットは向いている方向に $ A_i $ 進む
 
回転方向を適切に選ぶことで、$ N $ 回の操作後にロボットがいる座標を $ (X,Y) $ にすることはできますか？

できるならば、各操作において、右回りと左回りのどちらを選べばよいか求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 80 $
- $ 1\ \leq\ A_i\ \leq\ 10^7 $
- $ -10^9\leq\ X,Y\ \leq\ 10^9 $
- 入力は全て整数である
 
### Sample Explanation 1

最初ロボットは $ (0,0) $ にいて、$ x $ 軸正方向を向いています。次の手順により、$ N $ 回の操作後にロボットがいる座標を $ (X,Y) $ にできます。 - $ 1 $ 回目の操作：ロボットを左に $ 90 $ 度回転させ、$ y $ 軸正方向を向かせる。ロボットは向いている方向に $ A_1=3 $ 進み、ロボットのいる座標は $ (0,3) $ となる。 - $ 2 $ 回目の操作：ロボットを左に $ 90 $ 度回転させ、$ x $ 軸負方向を向かせる。ロボットは向いている方向に $ A_2=2 $ 進み、ロボットのいる座標は $ (-2,3) $ となる。 - $ 3 $ 回目の操作：ロボットを右に $ 90 $ 度回転させ、$ y $ 軸正方向を向かせる。ロボットは向いている方向に $ A_3=1 $ 進み、ロボットのいる座標は $ (-2,4) $ となる。 !\[図\](https://img.atcoder.jp/abc326/79baf4537d56c0df5c5d254e6e7f9616.png)

### Sample Explanation 3

`LLLL` や `RRRR` などでも正解となります。

## 样例 #1

### 输入

```
3 -2 4
3 2 1```

### 输出

```
Yes
LLR```

## 样例 #2

### 输入

```
1 0 0
1```

### 输出

```
No```

## 样例 #3

### 输入

```
4 0 0
1 1 1 1```

### 输出

```
Yes
LRRR```

## 样例 #4

### 输入

```
14 2543269 -1705099
3 14 159 2653 58979 323846 2643383 2795028 841971 69399 37510 58 20 9```

### 输出

```
Yes
LLLLLLLLLRLRRR```

# 题解

## 作者：樱雪喵 (赞：14)

## Description

有一个机器人位于坐标系原点 $(0,0)$，面向 $x$ 轴正方向。

在每一秒开始前，你可以选择让这个机器人向左或向右旋转 $90$ 度，不可以不转。接下来，机器人沿它面对的方向前进 $a_i$ 个单位距离，$i$ 为当前秒数。

给定总时间 $N$，序列 $a$ 和机器人最终的位置 $(X,Y)$。请构造一个合法的操作序列（用 `L` 和 `R` 表示每步操作的方向），或判断无解。

$N\le 80,\,a_i\le 10^7,\,-10^9\le X,Y\le 10^9$。
## Solution

因为不能不转弯，可以发现机器人一定是横竖交替行走的。进一步观察，发现奇数秒机器人只改变 $y$ 坐标，否则只改变 $x$ 坐标。

那么 $x,y$ 坐标是互不影响的，这启发我们把横纵坐标分开考虑。这里以横坐标为例，设序列 $a$ 的所有偶数位组成序列 $b$。

问题转化为给一个序列 $b$，可以自由选择每个 $b_i$ 的正负号，问是否存在方案使 $X=\sum b_i $。

这看起来像是值域极大的 01 背包，显然不太可做。从数据范围的角度考虑问题，$b$ 的长度至多只有 $40$。

考虑将序列 $b$ 拆成前后两部分，则每一半只有 $20$ 个数，对应着 $2^{20}$ 种状态。我们求出前一半的所有状态存进 `map`，在枚举后一半状态为 $x$ 时判断 $X-x$ 是否在 `map` 中存在即可。

时间复杂度 $O(\frac{n}{4}\times  2^{\frac{n}{4}})$。

```cpp
#define int long long
const int N=105;
int n,x,y;
int a[N],b[N],na,nb;
int ansa=-1,ansb=-1;
map<int,int> mp;
void solve()
{
    int sum=0;
    for(int i=1;i<=na;i++) sum+=-a[i];
    int lim=na/2;
    mp.clear();
    for(int i=0;i<(1<<lim);i++)
    {
        int res=0;
        for(int j=0;j<lim;j++)
            if(i>>j&1) res+=2*a[j+1];
        mp[res]=i;
    }
    for(int i=0;i<(1<<(na-lim));i++)
    {
        int res=0;
        for(int j=0;j<na-lim;j++)
            if(i>>j&1) res+=2*a[j+lim+1];
        if(mp.count(x-(sum+res))) {ansa=(i<<lim)+mp[x-sum-res];return;}
    }
}
char ans[N];
signed main()
{
    n=read(),y=read(),x=read();
    for(int i=1;i<=n;i++) 
    {
        if(i&1) a[++na]=read();
        else b[++nb]=read();
    }
    solve();
    swap(a,b),swap(na,nb),swap(ansa,ansb),swap(x,y);
    solve();
    swap(ansa,ansb);
    int to=1,aa=0,bb=0;
    if(ansa==-1||ansb==-1) {printf("No\n");return 0;}
    printf("Yes\n");
    for(int i=1;i<=n;i++)
    {
        if(i&1)
        {
            int now=ansa>>aa&1;
            if(now==0) ans[i]=((to==1)?'R':'L'),to=4;
            else ans[i]=(to==1)?'L':'R',to=2;
            aa++;
        }
        else
        {
            int now=ansb>>bb&1; bb++;
            if(now==0) ans[i]=(to==2)?'L':'R',to=3;
            else ans[i]=(to==2)?'R':'L',to=1;
        }
    }
    for(int i=1;i<=n;i++) printf("%c",ans[i]);
    printf("\n");
    return 0;
}
```

---

## 作者：Genius_Star (赞：3)

### 题意：

机器人位于坐标平面的原点，其中正 $x$ 轴指向右侧，正 $y$ 轴指向上方。

最初，机器人面向正 $x$ 方向。

您将按以下顺序对 $i=1,\cdots ,N$ 执行以下操作。

将机器人顺时针或逆时针旋转 $90$ 度。然后，机器人向前移动 $A_i$ 个单位。

是否可以选择旋转方向，使机器人在 $N$ 次操作后处于坐标 $(X,Y)$。

如果可能，确定每次操作应选择顺时针或逆时针方向。

### 思路：

因为 $n \le 80$，所以考虑爆搜。

直接爆搜是 $2^{80}$ 种可能，所以考虑优化。

因为每次操作，都是按照 $y$ 轴，$x$ 轴，$y$ 轴的顺序增加的，所以可以把对于 $x$ 轴的操作和对于 $y$ 轴的操作提取出来。

那么，这样两者分开爆搜的话，时间复杂度为 $O(2^{\frac{n}{2}})$，还是过不了。

考虑对于 $x$ 轴和 $y$ 轴的操作进行折半搜索，例如，增加 $x$ 轴的操作数量为 $l_1$，$y$ 轴的操作数量为 $l_2$。

那么先爆搜出 $1 \sim \frac{l_1}{2}$ 个操作可能造成的所有可能的 $x$ 轴的值，因为当前 $x$ 轴的位置和方向对于之后的移动不会有影响，所以在爆搜出 $\lceil \frac{l_1}{2} \rceil \sim l_2$ 对于 $x$ 轴可能增加的所有值之后。

对于每一种可能的值算一下还需要增加多少才可以到达目标值 $X$，设这个需要增加的值为 $k$，那么我们在$1 \sim \frac{l_1}{2}$ 个操作可能造成的所有可能的 $x$ 轴的值中找寻 $k$，如果有，那么可以使得 $X$ 轴到达目标。（可以用二分或者 set 实现），对于 $y$ 轴也一样进行折半搜索。

时间复杂度为：$O(2^{\frac{n}{4}})$。

**注意一下：最后输出答案的时候，对于每次 $x$ 轴与 $y$ 轴的操作，判断一下当前在哪个方向，转的方向是不同的。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=805,M=2000200;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll x;
	string s;
	bool operator<(const Node&rhs)const{
		return x<rhs.x;
	}
}d[M];
ll n,x,y,k,l1,l2,cnt=0;
ll a[N],b[N];
string t;
string ans[2];
bool F[2];
void dfs(ll* a,ll l,ll r,ll x,ll y,bool f,bool k){
	if(l==(r+1)){
		if(!f)
		  d[++cnt]={x,t};
		else{
			Node p={y-x,""};
			ll h=lower_bound(d+1,d+cnt+1,p)-d;
			if(d[h].x==y-x){
				ans[k]=d[h].s+t;
				F[k]=1;
			}
		}
		return ;
	} 
	t.push_back('+');
	dfs(a,l+1,r,x+a[l],y,f,k);
	t.pop_back();
	t.push_back('-');
	dfs(a,l+1,r,x-a[l],y,f,k);
	t.pop_back();
}
int main(){
	n=read(),x=read(),y=read();
	for(int i=1;i<=n;i++){
		k=read();
		if(i&1)
		  a[++l1]=k;
		else
		  b[++l2]=k;
	}
	dfs(a,1,l1/2,0,y,0,0);
	sort(d+1,d+cnt+1);
	dfs(a,l1/2+1,l1,0,y,1,0);
	cnt=0;
	dfs(b,1,l2/2,0,x,0,1);
	sort(d+1,d+cnt+1);
	dfs(b,l2/2+1,l2,0,x,1,1);	
	if(F[0]&&F[1]){
		puts("Yes");
		ll c1=0,c2=0,t=0;
		for(int i=1;i<=n;i++){
			if(i&1){
				if(ans[0][c1]=='+'){
					putchar(t==0?'L':'R');
					t=3;
				}
				else{
					putchar(t==0?'R':'L');
					t=1;
				}
				c1++;
			}
			else{
				if(ans[1][c2]=='+'){
					putchar(t==3?'R':'L');
					t=0;
				}
				else{
					putchar(t==3?'L':'R');
					t=2;
				}
				c2++;
			}
		}
	}
	else
	  puts("No");
	return 0;
}
```


---

## 作者：rainygame (赞：2)

这道题比较一眼吧……赛时 10 min 就想出来了。

首先 $N \le 80$，就考虑到一些指数级做法了。

从方向开始考虑，发现每次方向转变之后，要么是上下换左右，要么是左右换上下，我们把左右和上下分离开来，用它们来分别凑出 $x$ 和 $y$。这样 $N$ 减少了一半。

现在需要考虑的是一个新的问题：给定一个集合，可以将里面的一些数取负，求是否可以是它们的和为 $S$。

使用 meet-in-middle 即可解决这个问题，考虑对集合的前一半枚举取负的数，令取负后的和为 $s$，并存进 `map`。再枚举后一半取负的数，令取负后的和为 $s^\prime$，那么如果 `map` 里面有 $S-s^\prime$ 的数，就将这两个状态合并并返回。

最后结合上下和左右的状态输出方案即可。注意细节。

时间复杂度 $O(N+2^{\frac{n}{4}} \log 2^{\frac{n}{4}})$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, x, y, val, pos;
vector<int> a, b;

int fun(vector<int> vec, int s){
    if (vec.size() == 1){
        if (s == vec[0]) return 1;
        else if (s == -vec[0]) return 0;
        return -1;
    }
    map<int, int> mp;
    int siz1(vec.size()>>1), siz2(vec.size()-siz1);
    for (int i(0); i<(1<<siz1); ++i){
        int tmp(i), sum(0);
        for (int j(0); j<siz1; ++j){
            if (tmp & 1) sum += vec[j];
            else sum -= vec[j];
            tmp >>= 1;
        }
        mp[sum] = i;
    }
    for (int i(0); i<(1<<siz2); ++i){
        int tmp(i), sum(0);
        for (int j(0); j<siz2; ++j){
            if (tmp & 1) sum += vec[siz1+j];
            else sum -= vec[siz1+j];
            tmp >>= 1;
        }
        if (mp.count(s-sum)) return i<<siz1|mp[s-sum];
    }
    return -1;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> x >> y;
    for (int i(1); i<=n; ++i){
        cin >> val;
        if (i & 1) a.push_back(val);
        else b.push_back(val);
    }
    int ans1(fun(a, y)), ans2(fun(b, x));
    // cout << ans1 << ' ' << ans2 << '\n';
    if (ans1 == -1 || ans2 == -1){
        cout << "No";
        return 0;
    }

    pos = 1;
    cout << "Yes\n";
    for (int i(1); i<=n; ++i){
        if (i & 1){
            val = ans1 & 1;
            ans1 >>= 1;
            if (!((pos+val)&1)) cout << 'L';
            else cout << 'R';
        }else{
            val = ans2 & 1;
            ans2 >>= 1;
            if (pos+val == 1) cout << 'L';
            else cout << 'R';
        }
        pos = val;
    }

    return 0;
}

```


---

## 作者：HNOIRPplusplus (赞：1)

## 题意

+ 有一个机器人站在原点，面向 $x$ 轴的正方向。
+ 每一步机器人将**先**旋转 $90\degree$，**再**走 $A_i$ 个单位。
+ 求机器人最后能否落在 $(X,Y)$。

## 思路

~~乍一看我以为可以不旋转来着~~，既然每一步都需要旋转，那么实际上我可以得知如 $A_1, A_3, A_5,\dots$ 的步子将会在机器人面向和 $y$ 轴平行的方向时迈出；如 $A_2, A_4, A_6,\dots$ 的步子将会在机器人面向和 $x$ 轴平行的方向时迈出。于是问题就被拆成了两边的一维问题，即给定一些长度，可正可负，求最后能否凑出 $X$ 或者 $Y$。

再看数据范围，两边最多各有 $40$ 个长度元素，直接 $2^n$ 枚举显然是会超时的。于是我很自然的想到要进行~~砍价~~ Meet-in-the-middle。  
具体来说，我们可以算出前面一半 $\dfrac n 2$ 个元素一共能够凑出的 $2^{\frac n 2}$ 种可能的结果，并将他们存在一个方便访问的桶里面。遗憾的是，这 $2^{\frac n 2}$ 种结果太大了，没有办法直接存在一个 `bool` 数组做的桶里面，于是我只好牺牲了 $\log$ 的时间来调用 `map`。不过也并不会超时。方便的是，我们可以用位掩码来记录下该数字是如何被取得的，以便日后使用。  
然后枚举出后面一半 $\dfrac n 2$ 个元素所有的结果。算出一个来，我们立即检查在前面算出的结果中有没有可以和其凑成 $X$ 或者 $Y$ 的。具体来说，假设存在 $X_{\text前} + X_{\text后}=X$，则可以得到 $X_{\text前} = X - X_{\text后}$。你可能在说，为什么这么简单的式子我还要提一嘴呢？~~因为我考场上推错了挂了两罚。~~  

如果发现 $X$ 和 $Y$ 都凑得出来，那么我们直接调用前面记录的的位掩码以得知每一步前进的方向，再根据方向反推朝哪边旋转即可。

## 代码

欢迎欣赏屎山。

```cpp
// LUOGU_RID: 132396461
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 45;

int n, x, y;
int a[N], b[N], cnta, cntb, ansx = -1, ansy = -1;
map<int, int> xl, yl;

void dfs1(int sumy, int pos, int mask) {
  if(pos == cntb / 2 + 1) {
    yl[sumy] = mask;
    return;
  }
  dfs1(sumy + b[pos], pos + 1, mask + (1LL << pos));
  dfs1(sumy - b[pos], pos + 1, mask);
}

void dfs2(int sumy, int pos, int mask) {
  if(ansy != -1) {
    return;
  }
  if(pos == cntb + 1) {
    if(yl.find(y - sumy) != yl.end()) {
      ansy = yl[y - sumy] + mask;
    }
    return;
  }
  dfs2(sumy + b[pos], pos + 1, mask + (1LL << pos));
  dfs2(sumy - b[pos], pos + 1, mask);
}

void dfs3(int sumx, int pos, int mask) {
  if(pos == cnta / 2 + 1) {
    xl[sumx] = mask;
    return;
  }
  dfs3(sumx + a[pos], pos + 1, mask + (1LL << pos));
  dfs3(sumx - a[pos], pos + 1, mask);
}

void dfs4(int sumx, int pos, int mask) {
  if(ansx != -1) {
    return;
  }
  if(pos == cnta + 1) {
    if(xl.find(x - sumx) != xl.end()) {
      ansx = xl[x - sumx] + mask;
    }
    return;
  }
  dfs4(sumx + a[pos], pos + 1, mask + (1LL << pos));
  dfs4(sumx - a[pos], pos + 1, mask);
}

signed main() {
//  ios::sync_with_stdio(0);
//  cin.tie(0), cout.tie(0);
  cin >> n >> x >> y;
  for(int i = 1; i <= n; i++) {
    if(i % 2) {
      cin >> b[++cntb];
    } else {
      cin >> a[++cnta];
    }
  }
  dfs1(0, 1, 0);
  dfs2(0, cntb / 2 + 1, 0);
  dfs3(0, 1, 0);
  dfs4(0, cnta / 2 + 1, 0);
  if(ansx == -1 || ansy == -1) {
    cout << "No";
    return 0;
  }
  cout << "Yes\n";
  int facex = 1, powx = 2, facey = 1, powy = 2;
  for(int i = 1; i <= n; i++) {
    if(i % 2) {
      if(ansy & powy) {
        cout << (facex ? 'L' : 'R');
        facey = 1;
      } else {
        cout << (facex ? 'R' : 'L');
        facey = 0;
      }
      powy *= 2;
    } else {
      if(ansx & powx) {
        cout << (facey ? 'R' : 'L');
        facex = 1;
      } else {
        cout << (facey ? 'L' : 'R');
        facex = 0;
      }
      powx *= 2;
    }
  }
  return 0;
}

```

## 总结

[AC](https://atcoder.jp/contests/abc326/submissions/47078713)
[not AC](https://www.luogu.com.cn/record/132396461)


如果遇到 $O(2^n)$ 枚举会超时但是 $O(2^\frac n 2)$ 枚举不会超时的，并且分成两半再合并结果比较容易的，考虑 Meet-in-the-middle 算法。打 ABC 的时候手速和思维速度都是很重要的。

---

## 作者：FReQuenter (赞：1)

因为每次都必须旋转，所以奇数步是在 $y$ 轴上走的，其余实在 $x$ 轴上走的。

那么把这两种单独抽离出来，就变成算两遍“给一个序列添加加或减两种符号，使得和为一个特定的值”。现在 $n=\frac{80}{2}=40$，不能爆搜。

所以我们考虑双向搜索。先把数列的前 $\frac{n}{2}$ 位的可能答案搜出来，接着搜剩下的部分。最终只需要使用哈希/map 来判断两部分答案合起来和为特定值的数量就可以了。

接下来是输出。因为是左右转，所以当前的方向和添加的符号都会影响到下一位。所以我们可以记录在每个方向下一位添加号或减号需要左转还是右转。

复杂度 $O(2^{\frac{n}{4}}\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int N,X,Y,cntx,cnty,A[2][45];
vector<int> ans;
vector<vector<bool>> step;
vector<bool> tmp,anss[2];
bool flag[2];
map<int,int> mp;
void dfs1(int idx,int now,int lim,int sum){
	if(now==lim){
		ans.push_back(sum);
		step.push_back(tmp);
		return;
	}
	tmp.push_back(0);
	dfs1(idx,now+1,lim,sum+A[idx][now+1]);
	tmp.pop_back();
	tmp.push_back(1);
	dfs1(idx,now+1,lim,sum-A[idx][now+1]);
	tmp.pop_back();
}
void dfs2(int idx,int now,int lim,int sum){
	if(flag[idx]) return;
	if(now==lim){
		if(mp.count(sum)){
			flag[idx]=1;
			anss[idx]=step[mp[sum]];
			for(auto nx:tmp) anss[idx].push_back(nx);
		}
		return;
	}
	tmp.push_back(0);
	dfs2(idx,now+1,lim,sum+A[idx][now+1]);
	tmp.pop_back();
	tmp.push_back(1); 
	dfs2(idx,now+1,lim,sum-A[idx][now+1]);
	tmp.pop_back();
}
void solve(int idx,int m,int cnt){
	ans.clear();
	step.clear();
	int pos=cnt/2;
	dfs1(idx,0,pos,0);
	mp.clear();
	for(int i=0;i<ans.size();i++){
		mp[m-ans[i]]=i;
	}
	dfs2(idx,pos,cnt,0);
}
signed main(){
	cin>>N>>Y>>X;
	for(int i=1;i<=N;i++){
		if(cntx>cnty) cin>>A[1][++cnty];
		else cin>>A[0][++cntx];
	}
	solve(0,X,cntx);
	solve(1,Y,cnty);
	if(!flag[0]||!flag[1]) cout<<"No";
	else{
		cout<<"Yes\n";
		if(anss[1].size()<anss[0].size()) anss[1].push_back(0);
		string res="";
		bool dir=0;
		map<pair<bool,bool>,string> mp[2];
		mp[0][{0,0}]="LR"; 
		mp[0][{0,1}]="LL"; 
		mp[0][{1,0}]="RL"; 
		mp[0][{1,1}]="RR"; 
		mp[1][{0,0}]="RR"; 
		mp[1][{0,1}]="RL"; 
		mp[1][{1,0}]="LL"; 
		mp[1][{1,1}]="LR"; 
		for(int i=0;i<anss[0].size();i++){
			res+=mp[dir][{anss[0][i],anss[1][i]}]; 
			dir=anss[1][i];
		}
		if(N&1) res.pop_back();
		cout<<res;
	}
}
```

---

## 作者：forever_nope (赞：1)

经典问题，以前遇到过一个类似的问题：[[ABC082D] FT Robot](https://www.luogu.com.cn/problem/AT_arc087_b)。

建议对比着看一看这两道题，是两种不同的思路。

（那一道题不用输出方案，因此可以用 bitset 优化；而此题需要输出方案，因此需要双向搜索。

## 思路

注意到每次只能「左转」和「左转」。

所以，偶数次走的只改变 $x$ 坐标，奇数次走的只改变 $y$ 坐标。

因此，我们可以将 $x$ 方向和 $y$ 方向的分开来看，然后在将这两部分合并。

然后考虑每个方向的是怎么算？

问题转化为：

给定序列 $A$，可以改变任意元素的符号（正负），求一个方案，使得 $\sum A=x$。

显然，这是一个背包问题啦。

但是这样算来，复杂度是 $n\times2^n$ 的，明显不可过。

再仔细看看问题，我们发现可以双向搜索！

我们将序列分为左、右两半部分，对于每部分，分别求解，即求出每部分在该坐标轴上可以做出的贡献的集合，然后看看两个集合中是否有和为 $x$ 的。

但是本题似乎要输出方案？

发现方案最多有 $25$ 位，于是使用状压。

对于二进制数 $k$，我们规定，从后往前第 $i$ 为表示 $A_i$ 是否变成负数。

合并方案？我们进行操作的时候，是先操作左面的（前面的）。

因此我们将两个二进制数拼接在一起就可以了。

输出方案的时候，可以记录一个当前的方向，就很容易得出每次的转向了：

- 如果当前朝向«右»，接下来要往«上»走，则左转；
- 如果当前朝向«右»，接下来要往«下»走，则右转；
- （这个还用讲吗？。

注意：实现的时候，一定要注意二进制移位的细节！

时间复杂度：$O(n\times2^{n/2})$。

## 代码

评测记录：<https://atcoder.jp/contests/abc326/submissions/47085159>

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<int>;
using ml = map<int, ll>;

#define endl '\n'
#define rep(i, n) for (int i = 0; i < (n); ++i)

#define rr read()
inline int read() {
    int num = 0, flag = 1, ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') flag = -1;
    for (; isdigit(ch); ch = getchar()) num = num * 10 + ch - '0';
    return num * flag;
}

ml mean(vi x) {
    ml ret[2]; ret[0][0] = 0ll;
    int k = 0; rep(i, x.size()) {
        ret[k ^= 1].clear(); for (auto t : ret[k ^ 1])
        ret[k][t.first + x[i]] = t.second | (1 << i), ret[k][t.first - x[i]] = t.second;
    } return ret[k];
}

ll solve(vi a, int x) {
    int n = a.size();
    vi L, R; rep(i, n) (i < n / 2 ? L : R).push_back(a[i]);
    ml l = mean(L), r = mean(R);
    for (auto i : l)
        if (r.count(x - i.first)) return i.second | (r[x - i.first] << n / 2);
    printf("No\n"), exit(0);
}

signed main() {
    int N = rr, X = rr, Y = rr; vi x, y;
    rep(i, N) (i & 1 ? x : y).push_back(rr);
    ll a = solve(x, X), b = solve(y, Y);
    printf("Yes\n");
    int d = 1; rep(i, N) {
        if (i & 1) putchar(((a >> i / 2) & 1) == d ? 'R' : 'L'), d = ((a >> (i >> 1)) & 1);
        else putchar(((b >> i / 2) & 1) == d ? 'L' : 'R'), d = ((b >> (i >> 1)) & 1);
    } return 0;
}
```


---

## 作者：1234567890sjx (赞：1)

场上被这个题给炸飞了。~~虽然还是上了一大把分但是还是很难受。~~

十分的诈骗！

由于每一次机器人必须要旋转 $90^\circ$（不管是顺时针还是逆时针），所以每一次旋转过后走的方向平行的轴必然会发生一次正逆的变化。

那么把奇偶位分开考虑，判断输入操作组中奇数下标的元素是否可以把 $y$ 坐标需要走的方向的所有元素通过正负的变换来凑出来，偶数和 $x$ 坐标也是同理。

发现 $\frac{n}{2}\le 40$，直接暴搜判断每一个位置是否合法 $O(2^n)$ 是不可行的。

然后就是常规套路了：把奇数下标和偶数下标的元素分开处理，不管是奇数下标还是偶数下标的元素都分成前后两个部分（大小尽量的平均），通过 `Meet-In-Middle` 算法直接解决。

那么对于每一个部分处理的时间复杂度都是 $O(2^{n^{\frac{1}{4}}})$ 的。直接暴力处理即可。

代码细节很多。

由于我实现的极其不优美所以就不贴代码了。

---

## 作者：Mr_Biantainne (赞：0)

## 题外话
这次的 F 题好像比较好做，写篇题解。
## 题意分析
翻译把题意写得很清楚，这里就不再介绍了。接下来我们分析一下。

有一句话是：
> 将机器人顺时针或逆时针旋转 $90$ 度。然后，机器人沿着它所面对的方向向前移动 
$A_i$ 个单位。

可以发现，机器人显然是这样走的：纵坐标走一次、横坐标走一次、纵坐标走一次、横坐标走一次……

因此就可以将走的距离根据输入位置的奇偶性分开来看，题意就简化成了这样：
> 给定 $k$ 个数字 $B_1, B_2,...,B_k$，每一个数字都可以改变正负号。问如何才能使所有 $k$ 个数字的和等于指定的数字 $x$。

这个问题就是一个板子题了吧。
## 解决子问题
$n \le 80$，奇偶性分开看后可以发现 $k \le 40$。

$40$ 个数字，枚举每个数的正负性是 $O(2^k)$ 的时间复杂度，当然会超时。

那就可以把数字分成长度接近的两堆 $B_1,B_2,...,B_{\frac{k}{2}}$ 和 $B_{\frac{k}{2}+1},B_{\frac{k}{2}+2},...,B_k$，每堆最多 $20$ 个，再来枚举正负性，时间复杂度就变成了 $O(2^{\frac{k}{2}})$，最大就是 $O(2^{\frac{40}{2}}) = O(2^{20})$，不会超时。

在枚举第二堆的数字正负性的时候，设计算结果为 $ans$，则只要检查 $x-ans$ 在 $S_1$（第一堆中所有元素的正负组合的集合）中是否存在即可。

至于方案是怎么做的，那就可以设置一个二进制数 $i$，对于每一位，如果是 `+` 就将这一位设置为 $1$，如果是 `-` 就将这一位设置为 $0$。第一堆设置一个映射 $mp_1$，将得到的加和 $sum$ 与所对应的二进制数映射（即用 $sum$ 映射 $i$）。第二堆也设置映射 $mp_2$。 最后找到方案，只要将 $mp_1$ 和 $mp_2$ 拼接起来即可。

在写代码时，我们可以发现，因为是一边枚举第二堆的数字正负性，一边去查看 $mp_1$ 中的元素的，因此 $mp_2$ 可以省略。

### 子问题代码如下：
```cpp
for (ll i = 0; i < (1 << (k >> 1)); i++)
{
	ll j = i, rec = 0, ans = 0;
	for (ll p = 1; p <= k / 2; p++)
	{
		rec++; //记录目前在 a 的第几位
		ans += (2 * (j & 1) - 1) * a[rec]; //构造。如果 j 的这一位是 1 就加，是 0 就减。
		j /= 2;
	}
	mp[ans] = i;
}
for (ll i = 0; i < (1 << (k - (k >> 1))); i++)
{
	ll j = i, rec = k / 2, ans = 0; //注意 rec 从一般开始计数
	for (ll p = 1; p <= k - k / 2; p++)
	{
		rec++; 
		ans += (2 * (j & 1) - 1) * a[rec];
		j /= 2; 
	}
	if (mp.count(x - ans)) //能满足条件
	{
		num = (i << (k / 2)) + mp[x - ans]; //根据二进制数的存储方式，应当反过来拼接
		t = 1;
		break;
	}
}
```
这里设置了一个变量 $t$，最后如果变量 $t$ 的值为 $0$ 就说明此问题无解。
## 解决本题
本题计算完方案后，把 $x$ 轴和 $y$ 轴的移动重新放在一起，自己手画一个图来看看什么情况该左转，什么情况该右转。
### 全部代码（附注释）：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, x, y, a[45], b[45], num1, num2;
bool t1, t2;
map <ll, ll> mp;
ll xaxis = 1, yaxis; //当前 x 和 y 轴的指向 
string ans;
int main()
{
	cin >> n >> x >> y;
	for (ll i = 1; i <= (n >> 1); i++) cin >> b[i] >> a[i]; // 分奇偶性分别看 
	if (n & 1) cin >> b[(n + 1) >> 1]; // 多出来一个 
	// 第一部分 
	ll k = n >> 1;
	for (ll i = 0; i < (1 << (k >> 1)); i++)
	{
		ll j = i, rec = 0, ans = 0;
		for (ll p = 1; p <= k / 2; p++)
		{
			rec++;
			ans += (2 * (j & 1) - 1) * a[rec];
			j /= 2;
		}
		mp[ans] = i;
	}
	for (ll i = 0; i < (1 << (k - (k >> 1))); i++)
	{
		ll j = i, rec = k / 2, ans = 0;
		for (ll p = 1; p <= k - k / 2; p++)
		{
			rec++;
			ans += (2 * (j & 1) - 1) * a[rec];
			j /= 2; 
		}
		if (mp.count(x - ans))
		{
			num2 = (i << (k / 2)) + mp[x - ans];
			t2 = 1;
			break;
		}
	}
	mp.clear(); //记得清空！
	// 第二部分 
	k = (n + 1) >> 1;
	for (ll i = 0; i < (1 << (k >> 1)); i++)
	{
		ll j = i, rec = 0, ans = 0;
		for (ll p = 1; p <= k / 2; p++)
		{
			rec++;
			ans += (2 * (j & 1) - 1) * b[rec];
			j /= 2;
		}
		mp[ans] = i;
	}
	for (ll i = 0; i < (1 << (k - (k >> 1))); i++)
	{
		ll j = i, rec = k / 2, ans = 0;
		for (ll p = 1; p <= k - k / 2; p++)
		{
			rec++;
			ans += (2 * (j & 1) - 1) * b[rec];
			j /= 2; 
		}
		if (mp.count(y - ans))
		{
			num1 = (i << (k / 2)) + mp[y - ans];
			t1 = 1;
			break;
		}
	}
	if (!t1 || !t2) //不满足要求 
	{
		cout << "No";
		return 0;
	}
	cout << "Yes\n";
	for (ll i = 1; i <= (n >> 1); i++)
	{
		if (xaxis == 1) // x 轴向右 为正 
		{
			if (num1 & 1) // y 轴向上 为正 
			{
				ans.push_back('L'); // 左转 
				yaxis = 1; // 设置方向 
			}
			else // y 轴向下 为负
			{
				ans.push_back('R'); // 右转 
				yaxis = -1;
			}
		}
		else // x 轴向左 为负 
		{
			if (num1 & 1) // y 轴向上 为正
			{
				ans.push_back('R'); // 右转 
				yaxis = 1;
			}
			else // y 轴向下 为负
			{
				ans.push_back('L'); // 左转 
				yaxis = -1;
			}
		}
		num1 >>= 1; 
		if (yaxis == 1) // y 轴向上 为正
		{
			if (num2 & 1) // x 轴向右 为正 
			{
				ans.push_back('R'); // 右转
				xaxis = 1;
			}
			else // x 轴向左 为负 
			{
				ans.push_back('L'); // 左转
				xaxis = -1;
			}
		}
		else // y 轴向下 为负
		{
			if (num2 & 1) // x 轴向右 为正
			{
				ans.push_back('L'); // 左转
				xaxis = 1;
			}
			else // x 轴向左 为负 
			{
				ans.push_back('R'); // 右转
				xaxis = -1;
			}
		}
		num2 >>= 1;
	}
	if (n & 1) //多出来一个 
	{
		if (xaxis == 1)
		{
			if (num1 & 1)
			{
				ans.push_back('L');
				yaxis = 1;
			}
			else
			{
				ans.push_back('R');
				yaxis = -1;
			}
		}
		else
		{
			if (num1 & 1)
			{
				ans.push_back('R');
				yaxis = 1;
			}
			else
			{
				ans.push_back('L');
				yaxis = -1;
			}
		}
		num1 >>= 1;
	}
	cout << ans; //输出答案完结 
}
```
### 我的代码长达 $150$ 多行，写起来比较麻烦。如果大佬们有更好的解法，请多多指教，谢谢！

---

## 作者：Hellsing_Alucard (赞：0)

## [F](https://atcoder.jp/contests/abc326/tasks/abc326_f "F")

一道搜索好题。

一眼就可以看到 $n\le 80$，看起来直接暴搜不是很能过的样子，考虑优化。

因为每一次都要转向，所以可以可以考虑把 $x$ 轴和 $y$ 轴分开计算。

这样，时间复杂度就是 $2\times 2^{40}$。

还是不够，继续优化，因为直到初始状态和最终状态，所以可以考虑双向搜索优化。

最后输出答案需要注意，我们记录的信息是 $x$ 和 $y$ 的正负，转化成 `LR` 需要记录前一位的信息。

```cpp
int n,sx,sy;
map<int,string>mpx;
map<int,string>mpy;
map<int,int>mp;
int a[500];
vector<int>x,y;
inline void dfsx(int i,int pos,string s){
    if(i==x.size()/2){
        mpx[pos]=s;
        return;
    }
    dfsx(i+1,pos+x[i],s+"1");
    dfsx(i+1,pos-x[i],s+"0");
}
bool fl=0;
inline void dfsx2(int i,int pos,string s){
    if(i==x.size()){
        if(!mpx.count(sx-pos))return;
        mpx[sx]=mpx[sx-pos]+s;
		fl=1;
		return;
    }
	dfsx2(i+1,pos+x[i],s+"1");
    if(fl)return;
    dfsx2(i+1,pos-x[i],s+"0");
    if(fl)return;
}
inline void dfsy(int i,int pos,string s){
    if(i==y.size()/2){
        mpy[pos]=s;
        return;
    }
    dfsy(i+1,pos+y[i],s+"1");
    dfsy(i+1,pos-y[i],s+"0");
}
inline void dfsy2(int i,int pos,string s){
    if(i==y.size()){
        if(!mpy.count(sy-pos))return;
        mpy[sy]=mpy[sy-pos]+s;
		fl=1;
		return;
    }
	dfsy2(i+1,pos+y[i],s+"1");
    if(fl)return;
    dfsy2(i+1,pos-y[i],s+"0");
    if(fl)return;
}
inline void print(){
    puts("Yes");
    vector<int>ans;
    int i=0,j=0;
    while(i<mpy[sy].size()||j<mpx[sx].size()){
        if(i<mpy[sy].size())ans.push_back(mpy[sy][i]-'0'),i++;
        if(j<mpx[sx].size())ans.push_back(mpx[sx][j]-'0'),j++;
    }
    int la=0;
	 up(i,0,ans.size()-1) {
		if (ans[i]) {
			if (la==0) cout<<"L",la=1;
			else if (la==1) cout<<"R",la=0;
			else if (la==2) cout<<"R",la=1;
			else if (la==3) cout<<"L",la=0; 
		}
		else {
			if (la==0) cout<<"R",la=3;
			else if (la==1) cout<<"L",la=2;
			else if (la==2) cout<<"L",la=3;
			else if (la==3) cout<<"R",la=2; 
		}
	}
}
signed main(){
	n=read();sx=read();sy=read();
    up(i,1,n){
        a[i]=read();
        if(i&1)y.push_back(a[i]);
        else x.push_back(a[i]);
    }
    dfsx(0,0,"");
    dfsx2(x.size()/2,0,"");
    fl=0;
    dfsy(0,0,""); 
    dfsy2(y.size()/2,0,"");
    if(mpx.count(sx)&&mpy.count(sy))print();
    else puts("No");
    return 0;
}
```

---

## 作者：SSER_ZRQ (赞：0)

考虑每一个 $a_i$ 对答案的贡献。

由于每次操作必须改变方向，所以每一个 $i$ 只能对 $x$ 坐标与 $y$ 坐标中的一个产生贡献。

如果 $i \bmod 2 = 1$，则将对 $y$ 坐标产生 $\pm a_i$ 的贡献。

如果 $i \bmod 2 = 0$，则将对 $x$ 坐标产生 $\pm a_i$ 的贡献。

不难发现，达到 $x$ 坐标与 $y$ 坐标是相互独立的。

所以，$a_i$ 可以被分为两个集合 $a_1,a_3,a_5 \dots$ 与 $a_2,a_4,a_6 \dots$。

设序列 $b_{1 \dots m}$ 为 $b_i=a_{i \times 2-1}$，设序列 $c_{1 \dots k}$ 为 $c_i=a_{i \times 2}$。

题意转化为构造一个序列 $d_{1 \dots n}$，其中 $d_i \in \{1,-1\}$，使得:

$$\ \sum_{i=1}^{m} d_i \times b_i = y$$
$$\ \sum_{i=1}^{k} d_{i+m} \times c_i = x$$

达到 $x$ 坐标与 $y$ 坐标是相互独立的，故 $d_{1 \dots m}$ 与 $d_{m+1 \dots m+k}$ 可以分开构造。

直接枚举是 $O(2^{\frac{n}{2}})$ 的。

可以改成折半搜索，并用 map 维护。

不难记录路径。

设 $q$ 为 $2^{\frac{n}{4}}$，时间复杂度 $O(q \log q )$。

---


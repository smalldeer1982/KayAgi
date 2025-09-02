# The Butcher

## 题目描述

Anton plays his favorite game "Defense of The Ancients 2" for his favorite hero — The Butcher. Now he wants to make his own dinner. To do this he will take a rectangle of height $ h $ and width $ w $ , then make a vertical or horizontal cut so that both resulting parts have integer sides. After that, he will put one of the parts in the box and cut the other again, and so on.

More formally, a rectangle of size $ h \times w $ can be cut into two parts of sizes $ x \times w $ and $ (h - x) \times w $ , where $ x $ is an integer from $ 1 $ to $ (h - 1) $ , or into two parts of sizes $ h \times y $ and $ h \times (w - y) $ , where $ y $ is an integer from $ 1 $ to $ (w - 1) $ .

He will repeat this operation $ n - 1 $ times, and then put the remaining rectangle into the box too. Thus, the box will contain $ n $ rectangles, of which $ n - 1 $ rectangles were put in the box as a result of the cuts, and the $ n $ -th rectangle is the one that the Butcher has left after all $ n - 1 $ cuts.

Unfortunately, Butcher forgot the numbers $ h $ and $ w $ , but he still has $ n $ rectangles mixed in random order. Note that Butcher didn't rotate the rectangles, but only shuffled them. Now he wants to know all possible pairs $ (h, w) $ from which this set of rectangles can be obtained. And you have to help him do it!

It is guaranteed that there exists at least one pair $ (h, w) $ from which this set of rectangles can be obtained.

## 说明/提示

In the first test case, Butcher could only have a rectangle of size $ 4 \times 5 $ . Then the cuts could look like this (first the green cut was made, then the red one):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1819B/4604742f19434dbb2dfafc53d3bccc8f9c76c341.png)In the second test case, Butcher could have either a rectangle of $ 1 \times 3 $ or $ 3 \times 1 $ . The cuts would have looked like this (first the green cut was made, then the red cut):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1819B/a32b9e64b715c3348f2ec2b70f2c902cbff97240.png)In the third test case, Butcher did not make any cuts, so the rectangle is $ 10 \times 10 $ .

## 样例 #1

### 输入

```
4
3
1 2
3 5
1 3
3
1 1
1 1
1 1
1
10 10
4
3 2
5 5
2 2
8 7```

### 输出

```
1
4 5
2
1 3
3 1
1
10 10
1
13 7```

# 题解

## 作者：FFTotoro (赞：7)

## 前言

赛时没切出来，下大分，麻了。

赛后不敢相信这玩意只有 \*1900。

## 解法

本题有一个非常关键的 Key Conclusion：

- 答案最多只有 $2$ 种:

  1. 初始长方形的长等于最终 $n$ 个小长方形中最大的长；
  2. 初始长方形的宽等于最终 $n$ 个小长方形中最大的宽；
  
  原理：第一次切割必然把一个长方形切下来放进箱子里，如果横着切，那么这个小长方形的长等于初始长方形的长；否则小长方形的宽等于初始长方形的宽。
  
既然找到了可能的解，那么就尝试检验解的合法性。

一个解要合法，首先它的长和宽都必须是总面积的因数，如果不符合这个条件的一定不合法。

如果满足上面的条件，就可以进行下一步检查：具体地，我们把被放进箱子里地小长方形从箱子里往外一个一个拿，并尝试拼成目标图形。每一次先拿出长最大的小长方形，如果它的长等于目标图形的长，那么把它拼进去，目标图形的宽减去该图形的宽，箱子里减少一个长方形；否则就拿出宽最大的小长方形，如果它的宽等于目标图形的宽，那么拼进去，目标图形的长减去该图形的长，否则该解不合法。一直到 $n$ 个小长方形都拿完，目标图形的长宽都被减为 $0$，那么该解合法。

实现时略有不同：每一次检查时我们拿出了**所有的**长 / 宽最大的小长方形，假设本轮拿的是长最大的若干个小长方形，那么下一次只能拿宽最大的（因为接下来长最大的小长方形的长就没办法与目标图形的长相等）。

可以使用 `map` 维护这个过程。单组测试数据时间复杂度为 $O(n\log n)$。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool check(int x,int y,vector<pair<int,int> > a,bool f){
  map<pair<int,int>,int,greater<> > m1,m2;
  for(auto [x,y]:a)m1[make_pair(x,y)]++,m2[make_pair(y,x)]++;
  for(int c=0;c<a.size();f^=1){
    if(f){
      if(m1.begin()->first.first!=x)return false;
      while(m1.begin()->first.first==x){
        y-=m1.begin()->first.second,c++;
        if(!--m2[make_pair(m1.begin()->first.second,x)])
          m2.erase(make_pair(m1.begin()->first.second,x));
        if(!--m1[make_pair(x,m1.begin()->first.second)])
          m1.erase(make_pair(x,m1.begin()->first.second));
        // 该轮需要检查长最大的
      }
    }
    else{
      if(m2.begin()->first.first!=y)return false;
      while(m2.begin()->first.first==y){
        x-=m2.begin()->first.second,c++;
        if(!--m1[make_pair(m2.begin()->first.second,y)])
          m1.erase(make_pair(m2.begin()->first.second,y));
        if(!--m2[make_pair(y,m2.begin()->first.second)])
          m2.erase(make_pair(y,m2.begin()->first.second));
        // 该轮需要检查宽最大的
      }
    }
  }
  return true;
}
main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,mx=0,my=0,c=0; cin>>n;
    vector<pair<int,int> > a(n),r;
    for(auto &[x,y]:a)
      cin>>x>>y,mx=max(mx,x),my=max(my,y),c+=x*y;
    if(!(c%mx)&&check(mx,c/mx,a,1))r.emplace_back(mx,c/mx);
    if(mx!=c/my&&!(c%my)&&check(c/my,my,a,0))r.emplace_back(c/my,my);
    // 注意两种情况可能产生长宽一样的图形，要判掉
    cout<<r.size()<<endl;
    for(auto [x,y]:r)cout<<x<<' '<<y<<endl;
  }
  return 0;
}
```

---

## 作者：Zimo_666 (赞：2)

## D. The Butcher

首先我们考虑矩形的可选方案，显然由于题目要求和样例观察。我们可以得出因为在剪的时候总有一半是不去进行任何操作了，那么我们显然只有两种方案了。

即最后的长是长的最大值 $maxc$ 或者宽是宽的最大值 $maxk$。我们考虑由于剪纸这样一个操作对总面积没有影响，因此可以直接计算出最后的长宽了。

首先如果 $maxc$ 或 $maxk$ 不是总面积 $S$ 的因数那么显然不合法。

那么下面我们就可以直接模拟剪纸的过程即可，即在所有的纸中找到当前的需要的长或者宽直到找不到为止，然后再找长。如果当长和宽都不能被找到，那么显然方案不合法。否则合法。

实现可以用 `map` 或 `set`。

复杂度 $O(n \log n)$。



---

## 作者：wizardMarshall (赞：1)

[Link](https://www.luogu.com.cn/problem/CF1819B)


## 题意

一个长方形经过多次裁剪后得到一堆小长方形，求原长方形的长和宽。

## 思路

一开始的长方形会被砍一刀，切成两个小长方形 $a$ 和 $b$。$a$ 之后就放着不动了，$b$ 继续递归裁剪。

![t1](https://cdn.luogu.com.cn/upload/image_hosting/m30knqoa.png)

注意到第一次得到的长方形 $a$，它的长或者宽一定是原长方形的长或宽的其中一个。

再进一步，它的长或者宽一定是最大的，这样我们就可以得到两种情况。设 $a$ 长 $x$，宽 $y$：

1. 长为 $x$，宽为 $\dfrac{S}{x}$

2. 长为 $\dfrac{S}{y}$，宽为 $y$

我们会发现情况只有这两种。然后还要判断一下总面积 $S$ 是不是整除。


---

接下来就可以模拟了。拿第一种情况来讨论，初始长为 $x$，宽为 $\dfrac{S}{x}$，我们就可以找有哪些小长方形的长为 $x$，并且**之前未被使用**，这样我们就可以减去这个小长方形的宽。

宽无处可减之后又找有没有宽匹配的，继续减长。以此类推，直到最后长或者宽等于零。

可以用 `map` 或者 `set` 实现。

## 代码

```c++


#include <bits/stdc++.h>
using namespace std;

#define int long long


int read() {
	char s = getchar();
	while (s < '0' ||s > '9') {
		s = getchar();
	}int sum = 0;
	while (s >= '0' && s <= '9') {
		sum = sum * 10 + s - '0';
		s = getchar();
	}return sum;
}

pair <int, int> a[200005];

map <pair <int, int>, int, greater<> > mp1, t1;//greater使长或宽从大到小排序，mp1存储的是{长，宽}
map <pair <int, int>, int, greater<> > mp2, t2;//mp2存储的是宽，长}

signed main() {
	
	int t;
	cin >> t;
	while (t--) {
		int n = read();
		mp1.clear();//CF特性，多测清空
		mp2.clear();
		int S = 0, mxa = 0, mxb = 0;
		for (int i = 1; i <= n; i++) {
			a[i].first = read();
			a[i].second = read();
			mp1[{a[i].first, a[i].second}]++;
			mp2[{a[i].second, a[i].first}]++;
			S += a[i].first * a[i].second;//计算总面积
			mxa = max(mxa, a[i].first);//如上所述，找最大值
			mxb = max(mxb, a[i].second);
		}
		
		t1 = mp1, t2 = mp2;//做备份
		vector <pair <int, int > > ans;
		if (S % mxa == 0) {
			int nowa = mxa, nowb = S / mxa, flag = 1;
			while (1) {
				
				if (mp1.begin()->first.first != nowa) {//没有与之匹配的
					flag = 0;
					break;
				}
				while (mp1.begin()->first.first == nowa) {//都删完
					nowb -= mp1.begin()->first.second;
                    mp2[{mp1.begin()->first.second, nowa}]--;
			        if (!mp2[{mp1.begin()->first.second, nowa}]) {//mp2与mp1同步删除
			        	mp2.erase({mp1.begin()->first.second, nowa});
			        }
			        mp1[{nowa, mp1.begin()->first.second}]--;
			        if (!mp1[{nowa, mp1.begin()->first.second}]) {
			        	mp1.erase({nowa, mp1.begin()->first.second});
			        }
				}
				if (!nowa || !nowb)break;//出现0了就跳出
				
				
				if (mp2.begin()->first.first != nowb) {//宽的删除与长相同
					flag = 0;
					break;
				}
				while (mp2.begin()->first.first == nowb) {
					nowa -= mp2.begin()->first.second;
			        if (!--mp1[{mp2.begin()->first.second, nowb}]) {
			        	mp1.erase({mp2.begin()->first.second, nowb});
			        }
			        if (!--mp2[{nowb, mp2.begin()->first.second}]) {
			        	mp2.erase({nowb, mp2.begin()->first.second});
			        }
				}
				if (!nowa || !nowb)break;
			}
			if (flag) {
				ans.push_back({mxa, S / mxa});
			}
		}
		mp1 = t1;
		mp2 = t2;
		if (S % mxb == 0) {//另一种情况，大致相同
			int nowa = S / mxb, nowb = mxb, flag = 1;
			while (1) {
				if (mp2.begin()->first.first != nowb) {//注意这里是先删宽相同的，可以想想为什么
					flag = 0;
					break;
				}
				while (mp2.begin()->first.first == nowb) {
					nowa -= mp2.begin()->first.second;
			        if (!--mp1[{mp2.begin()->first.second, nowb}]) {
			        	mp1.erase({mp2.begin()->first.second, nowb});
			        }
			        if (!--mp2[{nowb, mp2.begin()->first.second}]) {
			        	mp2.erase({nowb, mp2.begin()->first.second});
			        }
				}
				if (!nowa || !nowb)break;
				
				
				if (mp1.begin()->first.first != nowa) {
					flag = 0;
					break;
				}
				while (mp1.begin()->first.first == nowa) {
					nowb -= mp1.begin()->first.second;
			        if (!--mp2[{mp1.begin()->first.second, nowa}]) {
			        	mp2.erase({mp1.begin()->first.second, nowa});
			        }
			        if (!--mp1[{nowa, mp1.begin()->first.second}]) {
			        	mp1.erase({nowa, mp1.begin()->first.second});
			        }
				}
				if (!nowa || !nowb)break;
				
			}
			if (flag) {
				ans.push_back({S / mxb, mxb});
			}
		}
		if (ans.size() == 2 && ans[0] == ans[1]) {//如果两种情况相同要特判一下
			printf("1\n%lld %lld\n", ans[0].first, ans[0].second);
			continue;
		}
		printf("%d\n", ans.size());
		for (auto i : ans) {
			printf("%lld %lld\n", i.first, i.second);
		}
	}
	
	
	
	
    return 0;
}


```

-----

upd：笔者代码都挤在主函数里了……可以分函数来写。

---

## 作者：Zi_Gao (赞：1)

## 前言

感觉大家写麻烦了，提供一种更为简单的方法。

## 正文

### 0x00 题目分析

正向思考，去拼凑出一个矩形显然很困难麻烦，不好做。不妨考虑反向思考，观察这个过程，若第一刀竖着切，那么舍去那一片必然是有最长的边，反向的说这样情况下，最长的长边一定是原始纸片的长边，确定了原始长边自然能确定原始宽边，用总面积除一下即可；反之第一刀横切也是一样。

现在问题转化为一个给定长宽的矩形，是否能用一些小矩形拼凑出，而且只有 $2$ 中情况需要检查（第一次横切或者竖切）。现在就很简单了，与刚才同理第一刀切出来的纸片一定有着最长的长边或者宽边，那么用一个数据结构维护，在剩下的纸片中寻找一个最长的长或者宽，若匹配当前的长或者宽则弹出这个纸片，若无匹配则当前情况不符合，并且算出剩下部分的长和宽，继续看能否拼凑出剩下的矩形。发现是相似的过程，循环递推即可。

### 0x01 代码实现

用两个 set 维护即可，注意两种情况可能相同。

```AC CODE
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE long long
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

struct Paper{
    long long x,y;
}ps[200010];

struct NODE{
    long long val;
    int id;
    bool operator < (const NODE o) const{
        return val==o.val?id<o.id:val<o.val;
    }
};

int n;
std::set<NODE> stx,sty;

bool check(register long long nowx,register long long nowy){
    register int i,id;
    stx.clear(),sty.clear();
    for(i=0;i<n;++i) stx.insert((NODE){ps[i].x,i}),sty.insert((NODE){ps[i].y,i});
    while(!(stx.empty()&&sty.empty())){
        if(!stx.empty()&&stx.rbegin()->val==nowx){
            id=stx.rbegin()->id;
            nowy-=ps[id].y;
            sty.erase((NODE){ps[id].y,id});
            stx.erase(--stx.end());
        }else if(!sty.empty()&&sty.rbegin()->val==nowy){
            id=sty.rbegin()->id;
            nowx-=ps[id].x;
            stx.erase({ps[id].x,id});
            sty.erase(--sty.end());
        }else return false;
    }
    return true;
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    int t=read();
    register int i;
    register long long sumar,maxx,maxy,x,y;
    register char a,b;
    while(t--){
        n=read();
        maxx=maxy=sumar=a=b=x=y=0;
        for(i=0;i<n;++i){
            ps[i].x=read();
            ps[i].y=read();
            sumar+=ps[i].x*ps[i].y;
            maxx=std::max(maxx,ps[i].x);
            maxy=std::max(maxy,ps[i].y);
        }
        if(!(sumar%maxx)&&check(maxx,sumar/maxx)) a=1,x=maxx,y=sumar/maxx;
        if(!(sumar%maxy)&&check(sumar/maxy,maxy)&&(sumar/maxy!=x&&maxy!=y)) b=1;
        print(a+b);putchar('\n');
        if(a) print(maxx),putchar(' '),print(sumar/maxx),putchar('\n');
        if(b) print(sumar/maxy),putchar(' '),print(maxy),putchar('\n');;
        
    }

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

## 总结

这样的题要反向思考，抓住不变和可以确定的量，进而去解题，例如本题中的最长边和最宽边以及面积总和，这些不变量便是解题切入点。

---

## 作者：LYY_yyyy (赞：0)

注意到第一刀一定保留一个长/宽，并且保留的这一维在之后只会递减。所以保留的这一维的长度只能是所有子矩形的最大值。又因为总面积固定，可以通过分讨保留哪一维算出 $h$ 和 $w$ 的可能值。由如上结论，答案只可能是 $0,1,2$。

问题转变为判断性问题。在不改变切的方向之前，有一维一定是相同的。并且这一维在之后只会递减，所以我们一定把有这一维的全部切光才行。我们已经分讨了第一刀的方向，即可确定之后每一刀的方向，而这一维的长度也可以通过长度的减少而唯一确定。于是模拟判断即可。

代码：
```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define pb emplace_back
#define int long long
using namespace std;
int T;
vector<pair<int,int> > g1[1000010],g2[1000010];
bool vis[1000010];
vector<pair<int,int> > ans;
long long tot=0;
bool solve(int mx)
{
	if(tot%mx) return 0;
	int l=mx,r=tot/mx;
	int al=l,ar=r;
	while(l&&r)
	{
		int p;p=r;
		for(auto o:g1[l]) if(!vis[o.second]) vis[o.second]=1,r-=o.first;
		if(r==p) return 0;
		if(r<0) return 0;
		if(r==0) return ans.pb(al,ar),1;
		p=l;
		for(auto o:g2[r]) if(!vis[o.second]) vis[o.second]=1,l-=o.first;
		if(l==p) return 0;
		if(l<0) return 0;
		if(l==0) return ans.pb(al,ar),1;
	}
}
signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--)
	{
		int x,y,n;cin>>n;
		vector<int> use;
		int mx1=0,mx2=0;
		ans.clear();tot=0;
		for(int i=1;i<=n;i++)
		{
			cin>>x>>y;
			tot+=1ll*x*y;
			use.pb(x);use.pb(y);
			mx1=max(mx1,x);mx2=max(mx2,y);
			g1[x].pb(y,i);g2[y].pb(x,i);
		}
		solve(mx1);
		for(int i=1;i<=n;i++) vis[i]=0;
		for(auto o:use) if(!vis[o]) vis[o]=1,g1[o].swap(g2[o]);
		for(auto o:use) vis[o]=0;
		if(solve(mx2)) 
		{
			pair<int,int> op=ans.back();ans.pop_back();
			swap(op.first,op.second);ans.pb(op);
		}
		for(int i=1;i<=n;i++) vis[i]=0;
		for(auto o:use) g1[o].clear(),g2[o].clear();
		if(ans.size()==2&&ans[0]==ans[1]) ans.pop_back();
		cout<<ans.size()<<"\n";
		for(auto o:ans) cout<<o.first<<' '<<o.second<<"\n";
	}
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

首先发现对于每一次切割，长和宽只会变化一次。

所以，答案最多只会有两种情况（其中 $S$ 为矩形的面积）：

1. $(\max\{a_i\},\frac{S}{\max\{a_i\}})$，其中需要满足 $S \bmod \max\{a_i\} = 0$。

2. $(\frac{S}{\max\{b_i\}},\max\{b_i\})$，其中需要满足 $S \bmod \max\{b_i\} = 0$。

那么，直接判断这两种情况即可。

首先一直将长与当前目标长一样的矩形丢进去，然后将宽与当前目标宽一样的矩形丢进去。

注意在更新长宽的时候，目标长宽也会发生变化，需要时时更新。

在目标长宽其中有一个更新为 $0$ 时，表示此情况成立；如果在更新过程中，发现没有任何一个矩形能够放进去了，表示此情况不成立。

为了代码的可读性，我们可以将 $(a_i,b_i)$ 用两个数组存起来，分别按照 $a_i > a_j$ 与 $b_i > b_j$ 进行排序。

# code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define int long long
#define re register

using namespace std;

typedef pair<int,int> pii;
const int N = 2e5 + 10;
int T,n,s;
bool vis[N];

struct square{
	int a;
	int b;
	int id;
}arr[N],brr[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline bool check(int a,int b){
	int ida = 1,idb = 1;
	for (re int i = 1;i <= n;i++) vis[i] = false;
	while (a > 0 && b > 0){
		while (ida <= n && vis[arr[ida].id]) ida++;
		int idxa = ida,idxb = idb;
		while (ida <= n && arr[ida].a == a){
			vis[arr[ida].id] = true;
			b -= arr[ida].b;
			ida++;
		}
		while (idb <= n && vis[brr[idb].id]) idb++;
		while (idb <= n && brr[idb].b == b){
			vis[brr[idb].id] = true;
			a -= brr[idb].a;
			idb++;
		}
		if (idxa == ida && idxb == idb) return false;
	}
	if (!a || !b) return true;
	return false;
}

signed main(){
	T = read();
	while (T--){
		int A = 0,B = 0,s = 0,num = 0;
		vector<pii> v;
		n = read();
		for (re int i = 1;i <= n;i++){
			arr[i].a = brr[i].a = read();
			arr[i].b = brr[i].b = read();
			arr[i].id = brr[i].id = i;
			s += arr[i].a * arr[i].b;
			A = max(A,arr[i].a);
			B = max(B,arr[i].b);
		}
		sort(arr + 1,arr + n + 1,[](const square &a,const square &b){
			if (a.a != b.a) return a.a > b.a;
			return a.b > b.b;
		});
		sort(brr + 1,brr + n + 1,[](const square &a,const square &b){
			if (a.b != b.b) return a.b > b.b;
			return a.a > b.a;
		});
		if (s % A == 0 && check(A,s / A)){
			num++;
			v.push_back({A,s / A});
		}
		if (s % B == 0 && check(s / B,B)){
			if (v.empty() || (v[0].fst != s / B || v[0].snd != B)){
				num++;
				v.push_back({s / B,B});
			}
		}
		printf("%lld\n",num);
		for (auto p:v) printf("%lld %lld\n",p.fst,p.snd);
	}
	return 0;
}
```

---

## 作者：hfjh (赞：0)

# CF1819B B. The Butcher 题解

## 题意

有一张 $h \times w$ 的纸片，现在对这张纸片进行 $n−1$ 次裁剪。每次裁剪后会将其中一半收归（即这一半不会再被裁剪）。

保证纸片不会被旋转。

告诉你最终裁剪后的 $n$ 张纸片长宽，问初始有多少 $h\times w$ 的纸片可以裁剪成这 $n$ 张纸片，输出所有可行解。

## 题解

考虑第一次剪的那一刀一定会保留下来一个 $h$ 或者 $w$。

$h_i$ 和 $w_i$ 分别求最大，然后有可能 $h = h_{max}$ 或者 $w = w_{max}$。

用面积先判断一次可不可以除尽。

之后 `check` 再模拟把一块块拼回去，看看有没有不合法的。

`check` 总的来说就是反复取 $w,h$ 最大的，然后减去这一块，若发现取出来的和当前 $w$ 或 $w$ 不相等，那么无解。

用 `set` 维护即可。
> check 部分手模一下应该就知道怎么搞。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll T, n, cans;
ll S, mxh, mxw;
ll hh, ww;
ll ansh[3], answ[3];
struct node{
	ll h, w;
};
struct ruleh{
	bool operator()(const node a, const node b){
		if(a.h == b.h) return a.w > b.w;
		return a.h > b.h;
	}
};
struct rulew{
	bool operator()(const node a, const node b){
		if(a.w == b.w) return a.h > b.h;
		return a.w > b.w;
	}
};
multiset<node, ruleh>fh, nh;
multiset<node, rulew>fw, nw;
void input(){
	cin>> n;
	for(int i = 1; i <= n; ++i){
		cin>> hh >> ww;
		fh.insert((node){hh, ww});
		fw.insert((node){hh, ww});
		S += 1ll * hh * ww;
		mxh = max(mxh, 1ll * hh);mxw = max(mxw, 1ll * ww);
	}
}
bool js(ll fwj){
	int type = fwj;
	ll h, w;
	if(fwj) h = mxh, w = S / mxh;	
	else h = S / mxw, w = mxw;	
	nw = fw;
	nh = fh;
	while(!nh.empty()){
		if(type){//h
			if((*nh.begin()).h != h) return 0;
			while((*nh.begin()).h == h){
				w -= (*nh.begin()).w;
				nw.erase((*nh.begin()));
				nh.erase(nh.begin()); 
			} 
			type ^= 1;
		}else{
			if((*nw.begin()).w != w) return 0;
			while((*nw.begin()).w == w){
				h -= (*nw.begin()).h;
				nh.erase((*nw.begin())); 
				nw.erase(nw.begin());
			} 
			type ^= 1;
		}
	}
	return 1;
}
void op(){
	if(S % mxh == 0 && js(1)){
		++cans;
		ansh[cans] = mxh;
		answ[cans] = S / mxh;
	}
	if(S % mxw == 0 && mxh != S / mxw && js(0)){
		++cans;
		ansh[cans] = S / mxw;
		answ[cans] = mxw;
	}
}
void output(){
	cout<<cans<<'\n';
	for(int i = 1; i <= cans; ++i){
		cout<<ansh[i]<<' '<<answ[i]<<'\n';
	}
}
void qk(){
	S = 0; 
	cans = 0;
	mxh = mxw = 0;
	fh.clear(), fw.clear();
}
int main(){
	cin>>T;
	while(T--){
		qk();
		input();
		op();
		output();
	}
}
```

---

## 作者：bsTiat (赞：0)

首先我们从头开始思考整个过程，容易发现一个很显然的性质。

- 要么长度最长的纸片的长度和初始纸片的长度相同，要么高度最高的纸片的高度和初始纸片的高度相同。

不妨设长度最长的纸片的长度和初始纸片的长度相同，另一种情况我们只需要把所有纸片的长宽翻转一下再做一遍即可。

现在假设我们已经知道了初始纸片的长度，然后就想要找宽度。

按照我们找长度的思路，一样地，可以发现，在剩下的纸片中，宽度最大的那张纸片的宽度，是剩下的纸片的宽度，因此，初始纸片的宽度就是剩下纸片中的最大宽度加上所有纸片中长度最长纸片的宽度。

所以我们现在知道了初始纸片的长宽，只需要判断能不能把所有纸片都放进去即可。

可以考虑每次把当前长度最长的纸片放进去，然后再放剩下的纸片中宽度最宽的，这样子剩下的图片就会缩小一圈，然后重复这个过程，如果全部恰好放进去了，就是一组合法的解。

然后精细实现即可，虽然觉得挺细节的一开始，但是写完发现，开完 long long 就直接一发过了。

```cpp
#include<bits/stdc++.h>
# define int long long
# define pii pair<int,int>
# define x first
# define y second
# define db exit(0);
using namespace std;
inline int rd(){
	int f=1,s=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c<='9'&&c>='0'){s=(s<<3)+(s<<1)+(c^48);c=getchar();}
	return s*f;
}
const int N = 2e5+5, X =  1e6+5;
int n,cnt;
bool used[N];
pii s[N],a,b,c;
set<int>W[X],H[X];
bool check(int a,int b){
	if((1ull*a*b==0)&&cnt==0) return 1;
	if(a<0||b<0) return 0;
	int sum=0;
	for(int i:W[a]){
		if(used[i]) continue;
		--cnt; sum+=s[i].y;
		H[s[i].y].erase(i);
	} 
	if(!sum) return 0; b-=sum; if(b<0) return 0;
	if(b==0) return !cnt;
	sum=0;
	for(int i:H[b]){
		if(used[i]) continue;
		--cnt; sum+=s[i].x;
		W[s[i].x].erase(i);
	}
	if(!sum) return 0; a-=sum; if(a<0) return 0;
	if(a==0) return !cnt;
	return check(a,b);
}
pii solve(){
	pii t=c; cnt=0;
	for(int i=1;i<=n;++i) used[i]=0;
	sort(s+1,s+1+n); reverse(s+1,s+1+n);
	int o=2,h=s[1].y,w=0,res; used[1]=1;
	while(o<=n&&s[o].x==s[o-1].x) h+=s[o].y,used[o]=1,o++;
	for(int i=o;i<=n;++i) if(s[i].y>t.y) t=s[i],w=s[i].x;
	else if(s[i].y==t.y) w+=s[i].x;
	for(int i=o;i<=n;++i) if(s[i].y==t.y) used[i]=1;
	for(int i=1;i<=n;++i) if(!used[i]) 
		W[s[i].x].insert(i),H[s[i].y].insert(i),++cnt;
	res=check(s[1].x-w,t.y);
	for(int i=1;i<=n;++i) W[s[i].x].clear(),H[s[i].y].clear();
	if(res) return make_pair(s[1].x,h+t.y);
	return c;
}
signed main(){
	c.x=c.y=0;
	int T=rd(),sum;
	while(T--){
		n=rd();
		for(int i=1;i<=n;++i)
			s[i].x=rd(),s[i].y=rd();
		a=solve(); 
		for(int i=1;i<=n;++i) swap(s[i].x,s[i].y);
		b=solve(); swap(b.x,b.y);
		sum=(a!=c)+(b!=c)-(a==b);
		sum=max(sum,0ll);
		printf("%lld\n",sum);
		if(a!=c) printf("%lld %lld\n",a.x,a.y);
		if((b!=c)&&(a!=b)) printf("%lld %lld\n",b.x,b.y);
	}
	return 0;
}
```


---

## 作者：buaa_czx (赞：0)

## 题目大意  
对于一个矩形，可以对它进行横向切割或竖向切割得到两个小矩形，并将其中一个放在盒子里（矩形不会翻转，且之后不再对盒子里的矩形进行切割）。这样，在 $n-1$ 次切割后将会得到 $n$ 个矩形。现给出这 $n$ 个矩形的长和宽，要求找到所有可能的最初大矩形。  
## 思路  
首先，初始矩形的面积是可以累加求出的。不难发现第一次分割要么切割出一个长最大的矩形，要么切割出一个宽最大的矩形，可以分两种情况讨论。  
判断出第一个切割出的矩形后，可以求出剩下的大矩形的长和宽，问题转化为剩下的所有小矩形能否构成指定长和宽的大矩形。如果这些小矩形可以构成大矩形，则一定满足小矩形中最长（或宽）的长与大矩形的长（或宽）相等，递归判断剩下的小矩形能否构成除去小矩形后的大矩形即可。  
由于在过程中大矩形的长和宽单调不增，因此可以分别对小矩形按长和宽两次降序排列，在处理过程中只需遍历一次即可。时间复杂度受排序的限制，为 $O(n \log n)$。
## 代码  
[code](https://codeforces.com/contest/1819/submission/211090115)
```cpp
struct Rect {
    long long h, w;
    bool exi;
} r[200010];
Rect *hh[200010], *ww[200010];
int n, hp, wp;
long long a;
int cmp_h(Rect *x, Rect *y) { return x->h > y->h; }
int cmp_w(Rect *x, Rect *y) { return x->w > y->w; }
bool operator==(Rect x, Rect y) { return x.w == y.w && x.h == y.h; }
int judge(long long H, long long W) {
    if (H == 0 || W == 0)
        return 1;
    if (H < 0 || W < 0)
        return 0;
    while (hh[hp]->exi == 0 && hp < n)
        hp++;
    while (ww[wp]->exi == 0 && wp < n)
        wp++;
    if (hp >= n || wp >= n)
        return 0;
    if (hh[hp]->h == H) {
        hh[hp]->exi = 0;
        return judge(H, W - hh[hp]->w);
    }
    if (ww[wp]->w == W) {
        ww[wp]->exi = 0;
        return judge(H - ww[wp]->h, W);
    }
    return 0;
}
void solve() {
    vector<Rect> ans;
    a = wp = hp = 0;
    cin >> n;
    rep(i, 0, n - 1) {
        cin >> r[i].h >> r[i].w;
        r[i].exi = 1;
        ww[i] = hh[i] = r + i;
        a += r[i].h * r[i].w;
    }
    sort(hh, hh + n, cmp_h);
    sort(ww, ww + n, cmp_w);
    if ((a - hh[0]->h * hh[0]->w) % hh[0]->h == 0) {
        hh[0]->exi = 0;
        if (judge(hh[0]->h, (a - hh[0]->h * hh[0]->w) / hh[0]->h)) {
            ans.pb(
                {hh[0]->h, (a - hh[0]->h * hh[0]->w) / hh[0]->h + hh[0]->w, 1});
        }
    }
    wp = hp = 0;
    rep(i, 0, n - 1) { r[i].exi = 1; }
    if ((a - ww[0]->w * ww[0]->h) % ww[0]->w == 0) {
        ww[0]->exi = 0;
        if (judge((a - ww[0]->w * ww[0]->h) / ww[0]->w, ww[0]->w)) {
            ans.pb(
                {(a - ww[0]->w * ww[0]->h) / ww[0]->w + ww[0]->h, ww[0]->w, 1});
        }
    }
    if (ans.size() == 2 && ans[0] == ans[1])
        ans.resize(1);
    cout << ans.size() << endl;
    rep(i, 0, ans.size() - 1) { cout << ans[i].h << " " << ans[i].w << endl; }
}
```

---


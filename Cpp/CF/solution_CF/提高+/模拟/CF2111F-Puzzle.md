# Puzzle

## 题目描述

You have been gifted a puzzle, where each piece of this puzzle is a square with a side length of one. You can glue any picture onto this puzzle, cut it, and obtain an almost ordinary jigsaw puzzle.

Your friend is an avid mathematician, so he suggested you consider the following problem. Is it possible to arrange the puzzle pieces in such a way that the following conditions are met:

- the pieces are aligned parallel to the coordinate axes;
- the pieces do not overlap each other;
- all pieces form a single connected component (i.e., there exists a path from each piece to every other piece along the pieces, where each two consecutive pieces share a side);
- the ratio of the perimeter of this component to the area of this component equals $ \frac{p}{s} $ ;
- the number of pieces used does not exceed $ 50\,000 $ .

Can you handle it?

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2111F/5e8146c7cb67cd5137b08d4c5a868b76edc5f346.png) For this figure, the ratio of the perimeter to the area is $ \frac{11}{9} $

## 说明/提示

In the first test case of the first test, the figure may look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2111F/550b1426c39a924d1ff94400ce41d9c55ab986ac.png)In the second test, the figures look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2111F/42a4c1add90002c0bac3d3e045506ffa0e542c66.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2111F/fc9fcd788c781c5076a12092b07af742c25e09d1.png)Note that the internal perimeter is also taken into account!

## 样例 #1

### 输入

```
2
1 1
31 4```

### 输出

```
20
3 7
3 8
6 4
6 5
3 5
4 4
4 5
4 3
3 4
5 3
5 4
5 7
3 6
4 6
5 5
5 6
4 7
4 8
6 6
6 7
-1```

## 样例 #2

### 输入

```
2
4 2
12 5```

### 输出

```
24
-7 2
-3 -3
-7 -5
-7 1
-3 2
-7 -2
-3 -5
-7 -6
-5 -6
-3 -4
-3 -6
-7 0
-6 -6
-7 -3
-5 2
-7 -1
-3 1
-4 -6
-3 0
-7 -4
-6 2
-4 2
-3 -1
-3 -2
5
0 0
0 1
1 0
-1 0
0 -1```

# 题解

## 作者：CJZJC (赞：2)

$\frac{p}{s} > 4$ 时一定无解。

我们假设构造出来的图形周长为 $p\times i$，面积为 $s\times i$。

发现这个周长比面积非常恶心，考虑固定一个判断另一个是否可以。

考虑用到小学老师教过的平移法。

![](https://cdn.luogu.com.cn/upload/image_hosting/7dm42vxy.png)

在长方形里挖掉一块后它的周长不变。

那么我们只要枚举周长 $p\times i$，再判断能否放下 $s\times i$ 的面积就可以了。

复杂度大概是 $O(i^2p)$，实际更快。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T,s,p;
signed main(){
    cin>>T;
    while(T--){
        cin>>p>>s;
        int tmp=__gcd(p,s);
        p/=tmp;
        s/=tmp;
        if(p>s*4){
            cout<<"-1\n";
            continue;
        }
        bool fl=0;
        for(int i=1;s*i<=50000;i++){
            int c=p*i;
            if(c%2!=0){
                continue;
            }
            for(int j=1;j<c/2;j++){
                int h=j,l=c/2-j;
                if(h*l<s*i){
                    continue;
                }
                if(s*i<h+l-1){
                    continue;
                }
                fl=1;
                cout<<s*i<<'\n';
                for(int i=1;i<=l;i++){
                    cout<<1<<' '<<i<<'\n';
                }
                for(int i=2;i<=h;i++){
                    cout<<i<<' '<<1<<'\n';
                }
                int tmp=s*i-l-h+1;
                for(int i=2;i<=h;i++){
                    for(int j=2;j<=l;j++){
                        if(tmp){
                            cout<<i<<' '<<j<<'\n';
                            tmp--;
                        }
                        else{
                            break;
                        }
                    }
                    if(!tmp){
                        break;
                    }
                }
                break;
            }
            if(fl){
                break;
            }
        }
        if(!fl){
            cout<<"-1\n";
        }
    }
}
```

---

## 作者：EmptyAlien (赞：2)

有趣的题目。

我们观察题目给的一个图然后就可以联想到小学奥数一个经典结论：

一个长方形横平竖直地削去一个角之后周长不变：

![](https://cdn.luogu.com.cn/upload/image_hosting/yi318dez.png)

例如这样整个实线围出的图形的周长与大长方形是相等的。

这启发我们枚举周长，看面积能否通过这种方式表示。

第一步，很重要，将比值约分成最简形式，只有这样周长才一定是其倍数。

首先周长一定是偶数，所以若输入为奇数则两者同时乘 $2$。

于是我们就可以知道长和宽的和，设长 $x$，宽 $y$ 那此时能用这种方法表示出来的面积范围为 $[x+y-1, xy]$。

显然下界是不会变的，而我们要尽可能让当前面积可以被表示，所以要尽可能提高上界即 $xy$ 取最大值。

我们可以得到 $x=\lfloor\cfrac{p}{4}\rfloor, y=\lceil\cfrac{p}{4}\rceil$

我们检查当前面积是否在其范围内，如果是面积太小了，那无能为力，如果是太大了，我们还有希望。

注意到 $xy=O(p^2),s=O(p)$，于是我们可以通过将 $p,s$ 同时乘上一个数让它逐渐进入范围内。

我们只需要从 $1$ 枚举乘上的倍数看是不是可以就行了。

知道了长宽之后就好办了，可以先把框架的 $x+y-1$ 个定好，然后只需要按照面积填进去就可以了。

---

为什么这样不会超过范围呢？

我们设最后乘上的倍数为 $k$。

那我们知道 $\lfloor\cfrac{kp}{4}\rfloor\lceil\cfrac{kp}{4}\rceil \ge ks$。

所以 $\cfrac{kp^2}{2} \ge s$。

在最坏情况下 $k$ 取最大值，此时 $p=2,s=100$，即使是这样 $k$ 也小于等于 $50$。（事实上大多数情况达不到这个上限）

此时 $ks \le 50000$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[200][200];
void work() {
    int p, s;
    cin >> p >> s;
    int tmp = __gcd(p, s);
    p /= tmp;
    s /= tmp;
    if (p % 2 == 1) p *= 2, s *= 2;
    int x = (p / 2) / 2, y = p / 2 - x;
    int i;
    for (i = 2; x * y < (s * (i - 1)); i++) {
        x = ((p * i) / 2) / 2, y = (p * i) / 2 - x;
    }

    p *= (i - 1);
    s *= (i - 1);

    if (s - x - y + 1 < 0) {
        cout << -1 << endl;
        return;
    }
    cout << s << endl;
    s -= x + y - 1;
    for (int i = 1; i < x; i++) cout << i << " " << 0 << endl;
    for (int i = 0; i < y; i++) cout << 0 << " " << i << endl;
    for (int i = 1; i < x; i++)
        for (int j = 1; j < y; j++)
            if (s) s--, cout << i << " " << j << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    while (T--) work();

    return 0;
}
```

---

## 作者：Bonely_Muffin (赞：0)

一共就十组询问，可以直接暴力枚举。

枚举周长 $C(C \bmod 2=0)$ 和面积 $S(S\leq50000)$，使得 $\frac{C}{S} = \frac{p}{s}$。接下来只需要判定 $(C,S)$ 是否是一组合法解。

考虑先满足周长等于 $C$，可以先构造一个“边框”形如：
$$(1,1), (1,2), (1,3), \cdots, (1,a)$$
和
$$(2,1), (3,1), \cdots, (b,1)$$

使得 $2(a+b)=C$。

然后在这个半包围边框的内部，再填充一些方块，使得面积等于 $S$，这样可以做到不改变周长。

那如何判定填充是否可行呢？我们发现，需要满足 $a+b-1 \leq S \leq ab$。

注意只要满足了 $2(a+b)=C$，$a$ 和 $b$ 就是可以自由选取的。那么为了让 $S$ 的上界尽量松，应选取 $a=\lfloor \frac{C}{2} \rfloor$ 和 $b=\lceil \frac{C}{2} \rceil$。

容易发现，如果如上的方法不能满足 $\frac{p}{s}$ 条件，就已经足够判定无解。时间复杂度 $O(T \cdot S)$。


```cpp
int main(){
	int T=read();
	while(T--){
		int p=read(),s=read();
		int g=__gcd(p,s); p/=g,s/=g; 
		if(p&1) p<<=1,s<<=1; //C应为一个偶数
		bool ok=false; 
		for(ll C=p,S=s;S<=50000;C+=p,S+=s){
			ll a=C>>2,b=(C>>1)-a;
			if(a*b>=S && a+b-1<=S){
				ok=true;
				printf("%lld\n",S);
				for(int i=1;i<=a;i++) printf("%d 1\n",i);
				for(int i=2;i<=b;i++) printf("1 %d\n",i);
				S-=a+b-1;
				for(int i=2;i<=a&&S;i++){
					for(int j=2;j<=b&&S;j++,S--){
						printf("%d %d\n",i,j);
					}
				}
				break;
			}
		}
		if(!ok) puts("-1"); 
	}

	return 0;
}

```

---

## 作者：qqqaaazzz_qwq (赞：0)

还是比较有意思的。

首先，我们枚举 $n$ 表示方块的总数量，然后我们看看周长最大/最小是多少。

* 周长的最大值为 $2n+2$。

* 排成一条线即可。

* 周长的最小值，就是把这 $n$ 个方块排成尽可能接近 $\sqrt n \times \sqrt n$ 的矩形，它的周长就是答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/g72ulka6.png)

这样对于输入的 $p,s$，我们枚举方块的数量 $n$（是 $s$ 的倍数），然后看看 $p$ 是否在 $n$ 能表示的范围内就好了。

下面是一种方法可以从周长最大调整到周长最小：

![](https://cdn.luogu.com.cn/upload/image_hosting/0q7as4sb.png)

最劣情况下，$p=1,s=50$，需要 $4 \times 10^4$ 个方块。

---

代码如下：

```cpp
#include <bits/stdc++.h>
#define FAST ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
int x,y;
int a[50010];

pair<int,int> get(int all){
	int minn = ceil(sqrt(all));
	//底是 minn
	minn = (all/minn)*2+2*minn+(all%minn==0? 0:2);
	int maxx = 2*all+2;
	//minn ~ maxx 都可以哦~
	return {minn,maxx};
}
void gen(int x,int all){
	int n = ceil(sqrt(all));
	for (int i=1;i<=n;i++) a[i] = 1;
	a[1] = all-n+1;
	int idx = 2;
	int cur = 2*all+2;
	while(cur!=x){
		a[idx]++;
		a[1]--;
		
		++idx;
		if(idx==n+1) idx = 2;
		cur -= 2;
	}
	cout << all << "\n";
	for (int i=1;i<=n;i++){
		for (int j=1;j<=a[i];j++) cout << i << " " << j << "\n";
	}
	return;
}

void solve(){
	int x,y;
	cin >> x >> y;
	int u = __gcd(x,y);
	x /= u;y /= u;
	if(x>2*y+2){
		cout << -1 << "\n";
		return;
	}
	for (int i=1;;i++){
		pair<int,int> ok = get(i*y);
		if(i*x>=ok.first&&i*x<=ok.second&&i*x%2==ok.first%2){
			gen(i*x,i*y);
			return;
		}
	}
}

signed main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Halberd_Cease (赞：0)

提供一个时间复杂度更优 $O(S)$ 的做法，其中 $S=50000$ 为最大面积。

首先证明 $\frac ps$ 的上界为 $4$，即单个正方体存在。考虑增量，增加一个面积最多增加 $2$ 的周长，因此不存在更高的上界。

考虑固定面积，要使周长最大，一定排开成一字，或者排成 L 型。也有可能排成一个蛇形但是后面我们不会用到，总之一定是一条线并且两端不相连。该周长最大值为 $2s+2$。因此对于一个定周长的图形我们也可以得出其面积下限。

定周长面积上限，考虑排成一个正方形（当周长为 $4$ 的倍数时可以排成，若只是 $2$ 的倍数则排成长宽差 $1$ 的长方形，若周长为奇数则无法拼成直接跳过即可），面积上界是 $(\frac p4)^2$。

还有一个性质，就是矩形挖掉一个角，周长不变。这个是小学数学知识。

也就是说我们只要确定了周长，面积的范围就一定可以确定，并且范围内的一定可以取到。

然后考虑 $p$ 和 $s$ 的比。首先分别除以他们的 $\gcd$，得到一个最简式，显然周长只能是 $kp$ 而面积只能是 $ks$。枚举 $k$ 从 $1$ 直到 $ks$ 超过 $50000$ 为止，可以算出周长 $kp$ 对应的面积范围，若 $ks$ 在其中，那么有答案，直接输出即可。

如果 $50000$ 内不存在那么整个数据范围内就无解。感性理解就是周长一定面积能在范围内全部取到。

[submission](https://codeforces.com/contest/2111/submission/323639877)。

---


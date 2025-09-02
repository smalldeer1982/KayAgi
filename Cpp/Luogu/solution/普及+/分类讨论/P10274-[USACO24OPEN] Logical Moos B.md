# [USACO24OPEN] Logical Moos B

## 题目描述

Farmer John 有一个布尔语句，包含 $N$ 个关键字（$1\le N<2\cdot 10^5$，$N$ 为奇数）。奇数位置仅出现 $\texttt{true}$ 或 $\texttt{false}$，偶数位置上仅出现 $\texttt{and}$ 或 $\texttt{or}$。

一个 $x \operatorname{OPERATOR} y$ 形式的短语，其中 $x$ 和 $y$ 为 $\texttt{true}$ 或 $\texttt{false}$，而 $\operatorname{OPERATOR}$ 为 $\texttt{and}$ 或 $\texttt{or}$ ，按如下规则求值：

- $x \operatorname{and} y$：如果 $x$ 和 $y$ 均为 $\texttt{true}$，则求值结果为 $\texttt{true}$，否则为 $\texttt{false}$。
- $x \operatorname{or} y$：如果 $x$ 或 $y$ 为 $\texttt{true}$，则求值结果为 $\texttt{true}$，否则为 $\texttt{false}$。

在求值该语句时，FJ 必须考虑 Moo 语言中的运算符优先级。与 C++ 类似，$\operatorname{and}$ 优先级高于 $\operatorname{or}$。更具体地说，在求值该语句时，重复以下步骤直至该语句仅包含一个关键字。

1. 如果语句中包含 $\operatorname{and}$，选择其中任意一个，并将其周围的短语替换为其求值结果。
2. 否则，该语句包含 $\operatorname{or}$。选择其中任意一个，并将其周围的短语替换为其求值结果。

可以证明，如果在指定的一个步骤中可以求值多个短语，那么选择哪一个求值并不重要；该语句最终的求值结果将始终相同。

FJ 有 $Q$（$1\le Q\le 2\cdot 10^5$）个询问。在每个询问中，他给你两个整数 $l$ 和 $r$（$1\le l\le r\le N$，$l$ 和 $r$ 均为奇数），并删除关键字 $l$ 到关键字 $r$ 之间的段。反过来，他希望用一个简单的 $\texttt{true}$ 或 $\texttt{false}$ 替换他刚刚删除的段，以使整个语句的求值结果为某个指定的布尔值。帮助 FJ 判断是否可行！ 

## 说明/提示

### 样例解释 1

我们来分析第一个询问：

如果我们删除段 $[1,1]$ 并替换为 $\texttt{true}$，那么整个语句将变为：

$\texttt{true and true or true}$

我们对位置 $2$ 处的 $\texttt{and}$

关键字求值，得到

$\texttt{true or true}$

由于我们没有剩下的 $\texttt{and}$ 关键字，我们必须求值 $\texttt{or}$ 关键字。求值结束后，余下的是

$\texttt{true}$

可以证明，如果我们用 $\texttt{false}$ 替换该段，该语句仍将求值为 $\texttt{true}$，因此我们输出 `N`，因为该语句不可能求值为 false。

对于第二个询问，我们可以将段 $[1,3]$
替换为 true，整个语句将求值为 $\texttt{true}$，因此我们输出 `Y`。

对于第三个询问，由于 $[1,5]$ 是整个语句，我们可以将其替换为任意内容，因此我们输出 `Y`。

### 测试点性质

- 测试点 $3-5$：$N,Q\le 10^2$。
- 测试点 $6-8$：$N,Q\le 10^3$。
- 测试点 $9-26$：没有额外限制。

## 样例 #1

### 输入

```
5 7
false and true or true
1 1 false
1 3 true
1 5 false
3 3 true
3 3 false
5 5 false
5 5 true```

### 输出

```
NYYYNYY```

## 样例 #2

### 输入

```
13 4
false or true and false and false and true or true and false
1 5 false
3 11 true
3 11 false
13 13 true```

### 输出

```
YNYY```

# 题解

## 作者：EnofTaiPeople (赞：7)

需要我来讲一下铜组该怎么通过吗？

对于一次 $[l,r]$ 的查询，考虑将 $[1,l)$ 和 $(r,n]$ 表示出来，如果能很方便的查询当前的运算值，这道题就能做了。

由于先进行与运算，所以我们可以想象一下将若干用与运算连接的数并在一起，用一个 `std::vector` 存起来，其中两个数之间的运算符都是或。

如果 `vector` 的大小很大，复杂度就会变得很劣质，但我们发现当 `vector` 的大小超过 $3$ 时，可以将中间的所有数字或起来合并。

于是暴力处理前后缀的 `vector`，暴力查询即可，时空复杂度线性：
```cpp
int T,n,K,b[N];
string s;
struct dat{
    vector<int>a;
    void rec(){
        if(a.size()>3){
            int i,k=0;
            for(i=a.size()-2;i;--i)k|=a[i];
            a={a[0],k,a.back()};
        }
    }
    dat operator&(const dat &z){
        vector<int>res=a;
        res.back()&=z.a[0];
        int r=z.a.size(),i;
        for(i=1;i<r;++i)res.push_back(z.a[i]);
        dat rp={res};
        rp.rec();return rp;
    }
    dat operator|(const dat &z)const{
        vector<int>res=a;
        for(int p:z.a)res.push_back(p);
        dat rp={res};
        rp.rec();return rp;
    }
    int val(){
        int res=0;
        for(auto &p:a)res|=p;
        return res;
    }
}f[N],g[N];
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z,v1,v2;
    cin>>n>>T;
    for(x=1;x<=n;++x){
        cin>>s;
        b[x]=s[0]==(x&1?'t':'a');
    }
    f[1]={{b[1]}};
    for(x=3;x<=n;x+=2){
        if(b[x-1])f[x]=f[x-2]&(dat){{b[x]}};
        else f[x]=f[x-2]|(dat){{b[x]}};
    }
    g[n]={{b[n]}};
    for(x=n-2;x>=1;x-=2){
        if(b[x+1])g[x]=(dat){{b[x]}}&g[x+2];
        else g[x]=(dat){{b[x]}}|g[x+2];
    }
    while(T--){
        cin>>l>>r>>s;
        k=s[0]=='t';
        dat rp={{k}};
        if(l>1){
            if(b[l-1])rp=f[l-2]&rp;
            else rp=f[l-2]|rp;
        }
        if(r<n){
            if(b[r+1])rp=rp&g[r+2];
            else rp=rp|g[r+2];
        }
        putchar(rp.val()==k?'Y':'N');
    }
    return 0;
}
```

---

## 作者：cff_0102 (赞：6)

显然可以直接将 $[l,r]$ 的一大串直接替换为目标布尔值，再计算结果，判断最后得到的结果是否与期望相同，而不需要去试应该填 `true` 还是 `false`。

那么原问题转化为：每次给出 $l,r,x$，将 $[l,r]$ 替换为 $x$ 再求值。

把整个表达式按 `or` 分隔成若干块，可以 $O(n)$ 预处理出：
1. 每一块的值；
2. 每一个 `true` 或 `false` 在哪一块；
3. 每一个 `true` 或 `false` 所在的块前面 `and` 起来的值；
4. 每一个 `true` 或 `false` 所在的块后面 `and` 起来的值；
5. 每一个 `true` 或 `false` 所在的块前面所有块的值 `or` 起来的值；
6. 每一个 `true` 或 `false` 所在的块后面所有块的值 `or` 起来的值。

将上面提到的六个值用六个数组存起来，下面分别把它们命名为 $a_i,b_i,bp_i,bs_i,ap_i,as_i$。

预处理后，对于每个询问，输入完 $l,r,x$，接着就可以这样 $O(1)$ 计算最后的值：
1. 若 $ap_l=1$，结果为 $1$；
2. 否则若 $as_r=1$，结果为 $1$；
3. 否则最终结果为“这个块”（$[b_l,b_r]$ 合并后的一大块）的最终结果。若 $bp_l=0$，结果为 $0$；
4. 若 $bs_r=0$，结果为 $0$；
5. 否则最终结果为 $x$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
string s[N];
bool f(string s){return s=="true";};
int a[N],b[N];
bool bp[N],bs[N],ap[N],as[N],aa[N];
int c[N];//每一块的第一个位置 
int cnt=0;
int n;
void init(){
	s[0]="or";
	for(int i=1;i<=n;i+=2){
		if(s[i-1]=="or"){
			//新的一块
			b[i]=++cnt;
			c[cnt]=i;
			bp[i]=1;
			a[cnt]=f(s[i]);
			ap[i]=ap[c[b[i]-1]]|a[cnt-1];
		}else{
			b[i]=cnt;
			bp[i]=a[cnt];
			a[cnt]&=f(s[i]);
			ap[i]=ap[c[b[i]-1]]|a[cnt-1];
		}
	}
	s[n+1]="or";
	cnt=0;
	for(int i=n;i>=1;i-=2){
		if(s[i+1]=="or"){
			bs[i]=1;
			aa[++cnt]=f(s[i]);
			as[i]=as[c[b[i]+1]]|aa[cnt-1];
		}else{
			bs[i]=aa[cnt];
			aa[cnt]&=f(s[i]);
			as[i]=as[c[b[i]+1]]|aa[cnt-1];
		}
	}
}
bool query(int l,int r,string x){
	if(ap[l])return 1;
	if(as[r])return 1;
	if(bp[l]==0)return 0;
	if(bs[r]==0)return 0;
	return f(x);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int q;cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	init();
	for(int i=1;i<=q;i++){
		int l,r;string x;cin>>l>>r>>x;
		if(query(l,r,x)==f(x))cout<<"Y";
		else cout<<"N";
	} 
	return 0;
}
```

---

## 作者：Left_i_Forever (赞：4)

$\Large{\text{Solution}}$

容易想到预处理修改段左右的值，直接 $\Omicron(1)$ 运算求值。因为要先与后或，所以我们处理出到当前位置，前面和后面要先与多少再或多少。 

代入 `true` 和 `false`，先与后或即可。

注意我们可以在不需要与的位置与 $1$，不需要或的位置或 $0$，避免分类讨论。

$\Large{\text{Code}}$

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, q;
string s[200010];
bool And[200010], Or[200010];
bool anD[200010], oR[200010];

bool check(int l, int r, int val)
{
	val &= And[l - 1];
	val &= anD[r + 1];
	val |= Or[l - 1];
	val |= oR[r + 1];
	return val;
}

int main()
{
//	freopen ("prob1.in", "r", stdin);
//	freopen ("prob1.out", "w", stdout);
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> s[i];
	s[0] = "and", Or[0] = 0, And[0] = 1;
	s[n + 1] = "and", oR[n + 1] = 0, anD[n + 1] = 1;
	for (int i = 2; i <= n; i += 2)
	{
		if (s[i] == "and")
			Or[i] = Or[i - 2], And[i] = (s[i - 1] == "true" ? 1 : 0) & And[i - 2];
		else Or[i] = Or[i - 2] || And[i - 2] && (s[i - 1] == "true" ? 1 : 0), And[i] = 1;
	}
	for (int i = n - 1; i >= 1; i -= 2)
	{
		if (s[i] == "and")
			oR[i] = oR[i + 2], anD[i] = (s[i + 1] == "true" ? 1 : 0) & anD[i + 2];
		else oR[i] = oR[i + 2] || anD[i + 2] && (s[i + 1] == "true" ? 1 : 0), anD[i] = 1;
	}
	while (q--)
	{
		int l, r;
		string want;
		cin >> l >> r >> want;
		bool Want = (want == "true");
		if (check (l, r, 1) == Want || check (l, r, 0) == Want)
			cout << "Y";
		else cout << "N";
	}
	return 0;
}
```

---

## 作者：qinmingze (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P10274)

### 思路

这题是一道模拟题。

对于这道题目，我们首先要注意的是本题的位运算的优先级，我们需要**先进行**与运算，**再进行**或运算，因此本题我们可以考虑以**或运算符**为每一块的界限，将整个序列分为 $c$ 块，这样最后的答案就是每一块进行完或运算的值了。具体的操作方法如下：

### 预处理

我们需要预处理两个数组，其中一个是用来计算前 $i$ 个数中，值为 $\texttt{false}$ 出现的次数。另一个则是用来处理在前 $i$ 个块中，块的值为 $\texttt{true}$ 的个数。这样的统计方法，可以让我们在接下来的操作中更加的方便。

### 询问

对于每次询问，我们分为四种情况来处理。

#### 第一种情况：序列的返回值和询问的值都为 $\texttt{true}$。

- 如果当前范围在同一块内，那么我们只需要将当前的运算区间换成 $\texttt{true}$ 就可以了，这种情况是肯定有解的，我们输出 $\texttt{Y}$ 即可。

- 如果当前范围不在同一块内，我们需要判断当前所有块的值为 $1$ 的出现地方是否全在当前区间内，如果不再，那么即使最终当前区间的值是 $\texttt{false}$ 也**不会影响最终答案**，因此我们直接输出 $\texttt{Y}$ 就可以了。如果在，那么我们必须保证**左端点**所对应的块的**剩余位置**和**右端点**所对应的块的**剩余位置**必须全部为 $\texttt{true}$ 才可以，这样我们才能保证所有的块中，至少有一个块的值为 $\texttt{true}$，也就是保证最终的结果为 $\texttt{true}$。

#### 第二种情况：序列的返回值和询问的值都为 $\texttt{false}$。

这种情况比较简单，因为都为 $\texttt{false}$ ，所以我们可以直接将我们要更改的区间的值定为 $\texttt{false}$ 即可。也就是说，这种情况是**肯定有解**的。

#### 第三种情况：序列的返回值是 $\texttt{true}$，但询问的值是 $\texttt{false}$。

这种情况也相对简单，因为我们需要将序列最后的值从 $\texttt{true}$ 变为 $\texttt{false}$，因此我们需要保证所有区间值为 $1$ 出现的地方**全在**当前区间，这样我们将当前区间的值赋值为 $\texttt{false}$ 就可以了，这也是**唯一**一种有解的情况。

#### 第四种情况：序列的返回值是 $\texttt{false}$，但询问的值是 $\texttt{true}$。

- 如果左端点和右端点在一个块内，我们只需要保证当前块中 $0$ 出现的所有地方都在我们的更改区间内就可以了。因为当前最终答案的返回值为 $\texttt{false}$，所以所有块最后的值都是 $\texttt{false}$，我们如果想让最后的答案变为 $\texttt{true}$，就必须让当前块的值变为 $\texttt{true}$，那这种值只有在上面那种情况下才会出现。

- 不同块的情况，我们根据相同块的情况进行思考，我们必须要让当前能进行更改的区间所在块的值为 $\texttt{true}$ 才能让答案成立，因此**两个端点**所对应的块中**多余的部分**必须都是 $\texttt{true}$ 才可以。

### 代码


```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int cnt[N][2], sum0[N], sum2[N];

int ct[N];

int z[N], a[N], q[N];

int l[N], r[N];

int id[N];

int main(){
	int n, m;
	cin >> n >> m;
	int c = 1; 
	l[1] = 1;
	for(int i = 1; i <= n; i++){
		string s;
		cin >> s;
		id[i] = c;
		if(i % 2 == 1){
			if(s == "true") cnt[c][1]++, a[i] = 1;//记录 true 在第 i 个区间出现的次数。
			else cnt[c][0]++, a[i] = 0;//记录 false 在第 i 个区间出现的次数。
			ct[c]++;
		}else{
			if(s == "and") continue;
			else c++, r[c - 1] = i - 1, l[c] = i + 1;//维护每一个区间的左端点和右端点。
		}
	}
	r[c] = n;
	for(int i = 1; i <= c; i++){
		if(cnt[i][1] > 0 && !cnt[i][0]) z[i] = 1;//如果没有 false，当前的区间的值才能是 true。
		else z[i] = 0;
	}
	for(int i = 1; i <= n; i++) sum2[i] = sum2[i - 1] + z[i];//维护块的值为 true 的前缀和。
	for(int i = 1; i <= n; i++){//维护值为 false 的前缀和。
		if(i & 1) sum0[i] = sum0[i - 1] + (a[i] ^ 1);
		else sum0[i] = sum0[i - 1];//是符号，直接跳过。
	}
	int ans = 0;
	for(int i = 1; i <= c; i++) ans |= z[i];
	for(int i = 1; i <= m; i++){
		int x, y;
		string s;
		cin >> x >> y >> s;
		if(x == 1 && y == n){//如果能全部更改肯定就是可以的。
			q[i] = 1; continue;
		}
		if(s == "true"){//询问是否可以为 true。
			int s = id[x], t = id[y], qans;
			if(s == t){
				int tmp = 0;
				if(ans == 1) q[i] = 1;//第一种情况。
				else{//第四种情况
					if(sum0[y] - sum0[x - 1] == sum0[r[s]] - sum0[l[s] - 1]) q[i] = 1;
					else q[i] = 0;
				}
			}else{
				int tmp = 0;
				if(ans == 1){//第一种情况。
					if(sum2[t] - sum2[s - 1] == sum2[c]){
						if(sum0[x - 1] - sum0[l[s] - 1] == 0 && sum0[r[t]] - sum0[y] == 0) q[i] = 1;
						else q[i] = 0;
					}else q[i] = 1;
				}
				else{//第四种情况。
				    bool flag = 0;
					if(sum0[x - 1] - sum0[l[s] - 1] == 0 && sum0[r[t]] - sum0[y] == 0) flag = 1;
					if(flag) q[i] = 1;
					else q[i] = 0;
				}
			}
		}else{
			int s = id[x], t = id[y], qans;
			if(s == t){
				int tmp = 0;
				if(ans == 0) q[i] = 1;//第二种情况。
				else{//第三种情况。
					if(sum2[t] - sum2[s - 1] == sum2[n]) q[i] = 1;
					else q[i] = 0;
				}
			}else{
				int tmp = 0;
				if(ans == 0) q[i] = 1;//第二种情况。
				else{//第三种情况。
				    bool flag = 0;
					if(sum2[t] - sum2[s - 1] == sum2[n]) flag = 1;
					if(flag) q[i] = 1;
					else q[i] = 0;
				}
			}
		}
	}
	for(int i = 1; i <= m; i++){
		if(q[i] == 1) cout << 'Y';
		else cout << 'N';
	}
}
```

---

## 作者：zcq_qwq (赞：3)

Update 2025.5.18：发现本题解的一处错误并修正。

## 说在前面

这题其实并不难。只是需要分类讨论的东西有点多（反正我代码里挺多的）。

## 题目分析

这里提供一种简单粗暴的方法，只不过代码很长，但是还是能理解的。

首先我们把序列分块，因为 $\texttt {and}$ 的优先级比 $\texttt {or}$ 高，所以用 $\texttt {or}$ 作为块与块的分隔符。

先说一下定义：

1. $belong_i$：$i$ 所属的块。
2. $st_i$：$i$ 这个块的起始位置。
3. $ed_i$：$i$ 这个块的结束位置。
4. $s_i$：$1$ 到 $i$ 一共有多少个 $\texttt {true}$。
5. $s2_i$：$i$ 这个块里有一共有多少个 $\texttt {true}$。
6. $s3_i$：$i$ 这个块里是否全是 $\texttt{true}$。
7. $s4_i$：从块 $1$ 到块 $i$ 一共有多少个块全是 $\texttt{true}$。
8. $cnt$：一共有多少个块全是 $\texttt{true}$。

接下来，分类讨论。

1. $belong_l = belong_r$ 时。
    + 要求的结果是 $\texttt {true}$ 时。
      - 若 $s3_{belong_l} = 1$ 或 $s3_{belong_l} = 0$ 且 $cnt \ge 1$，可以构造（有其他块是 $\texttt{true}$ 或自己是 $\texttt{true}$）。
      - 若 $$\displaystyle \frac{ed_{belong_l} - st_{belong_l} + 2}{2} - \frac{r - l + 2}{2} = s2_{belong_l} - (s_r - s_{l - 2})$$，可以构造（自己可以变成 $\texttt{true}$）。
      - 否则，不能构造。
    + 要求的结果是 $\texttt{false}$ 时。
      - 若 $cnt = 0$ 或 $s3_{belong_l} = 1$ 且 $cnt = 1$，可以构造。（全为 $\texttt{false}$ 或者除自己外全为 $\texttt{false}$）
      - 否则，不能构造。
2. $belong_l \neq belong_r$ 时。
   + 要求的结果是 $\texttt{true}$ 时。
     - 若 $$s4_{belong_l - 1} + s4_{belong_n} - s4_{belong_r} \ge 1$$，可以构造。
     - 若 $$\displaystyle \frac{ed_{belong_r} - st_{belong_l} + 2}{2} - \frac{r - l + 2}{2} = s_{ed_{belong_r}} - s_{st_{belong_l} - 2} - s_r + s_{l - 2}$$，可以构造。（除了自己这一坨以外有其他块是 $\texttt{true}$，或自己可以变成 $\texttt{true}$）
     - 否则，不能构造。
   + 要求的结果是 $\texttt{false}$ 时。
     - 若 $$s4_{belong_l - 1} + s4_{belong_n} - s4_{belong_r} = 0$$，可以构造。（全是 $\texttt{false}$）
     - 否则，不能构造。

至此，讨论结束，相信你一定可以 AC 此题了。

## 注意事项

区间的形式类似于这样：$\texttt{true and false or true}$，每两个值之间都间隔了一个运算符。所以在获取区间长度的时候要 $\displaystyle \frac{r - l + 2}{2}$。

## 完整代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 200000;

int st[N], ed[N], belong[N], s[N], s2[N], s4[N];

bool s3[N];

int n, m, tot = 1;

string a[N];

string ans;

int main() {
	memset(st, 0x3f, sizeof st);
	memset(ed, 0, sizeof ed);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		s[i] = s[i - 1] + (a[i] == "true");
	}
	for (int i = 1; i <= n; i += 2) {
		belong[i] = tot;
		if (a[i + 1] == "or") {
			tot++;
		}
		st[belong[i]] = min(st[belong[i]], i);
		ed[belong[i]] = max(ed[belong[i]], i);
	}
	for (int i = 1; i <= n; i += 2) {
		s2[belong[i]] += (a[i] == "true");
	}
	int cnt = 0;
	for (int i = 1; i <= tot; i++) {
		s3[i] = (s2[i] == (ed[i] - st[i] + 2) / 2);
		if (s3[i]) {
			cnt++;
		}
	}
	for (int i = 1; i <= tot; i++) {
		s4[i] = s4[i - 1] + (s3[i] == 1);
	}
	for (int i = 1; i <= m; i++) {
		int l, r;
		cin >> l >> r;
		string opt;
		cin >> opt;
		bool tmp = (opt == "true");
		if (belong[l] == belong[r]) {
			if (tmp == true) {
				int len = (r - l + 2) / 2;
				if (s3[belong[l]] || !s3[belong[l]] && cnt >= 1) {
					ans.push_back('Y');
				} else if ((ed[belong[l]] - st[belong[l]] + 2) / 2 - len == s2[belong[l]] - (s[r] - s[l - 2])) {
					ans.push_back('Y');
				} else {
					ans.push_back('N');
				}
			} else {
				if (cnt == 0 || s3[belong[l]] && cnt == 1) {
					ans.push_back('Y');
				} else {
					ans.push_back('N');
				}
			}
		} else {
			int dl = belong[l], dr = belong[r];
			if (tmp == true) {
				if (s4[dl - 1] + s4[belong[n]] - s4[dr] >= 1 || (ed[dr] - st[dl] + 2) / 2 - (r - l + 2) / 2 == s[ed[dr]] - s[st[dl] - 2] - s[r] + s[l - 2]) {
					ans.push_back('Y');
				} else {
					ans.push_back('N');
				}
			} else {
				if (s4[dl - 1] + s4[belong[n]] - s4[dr] == 0) {
					ans.push_back('Y');
				} else {
					ans.push_back('N');
				}
			}
		}
	}
	cout << ans;
	return 0;
}
```

于是这篇简单粗暴又不失优雅的题解就此结束。

## 说在后面

若本篇题解讲解有误，欢迎提出。

---

## 作者：complete_binary_tree (赞：3)

今年的 $\text{USACO Cu}$ 组第一题难度还行，但是这码量雀食有点多。（或者是我的问题）

给出一份详细的题解：

---

给你一个表达式串（仅包含 ```and```，```or```，```true``` 和 ```false```），保证合法（即奇数位是 ```true/false```，偶数位是 ```and/or```）。

然后要把一整串合法表达式区间 $[l,r]$ 变成 ```true/false```（可以变成任意一个，但是 **不能不变**），问能否使表达式最终的值变为给定的值（```true/false```）。保证 $l,r$ 合法，即 $l,r$ 都是奇数。

注意：```and``` 优先级大于 ```or```。

例如：

```
true or false and true
5 5 false
1 3 false
1 5 false
```

样例 $1$ 中，无论如何变换，都没办法让它变成 ```false```。

样例 $2$ 中，可以通过以下变换变成 ```false```：

```
{true or false} and true => false and true
```

样例 $3$ 可以把所有换成一个 ```false```。

---

我们可以在每一个 ```or``` 处把序列分隔，如：

```
true or false and false and true or false and true
```

变成

```
{true} or {false and false and true} or {false and true}
```

然后定义数组 ```pre``` 和 ```suf```，其中：

- ```pre[i]```：

  - 如果序列的第 $i$ 个是 ```and```：
    
    那么里面存的就是 从上一个 ```or``` 到现在这个 ```and``` 的开区间的表达式的值。
    
    如：```true or false and false and true```
    
    那么 ```pre[4]``` 存的是 ```(2, 4) = false``` 的值，```pre[6]``` 存的是 ```(2, 6) = false and true = false``` 的值。
    
    这样的话，我们转移的时候只要考虑下面两种情况
    
    - 序列第 $i - 2$ 位置是 ```or```
      
      那只要存序列 $i - 1$ 位置的值就行了。
      
    - 序列第 $i - 2$ 位置是 ```and```
    
      那也好办，因为 ```&``` 是满足交换律的，所以直接让 ```pre[i - 2] &``` 上序列 $i-1$ 位置的值即可。 
    
  - 如果序列的第 $i$ 个是 ```or```：
  
    那么 ```pre[i]``` 存的就是 $[1,i)$ 的表达式的值。
    
    如：```true or false and true or true```
    
    那么 ```pre[2]``` 存的是 ```[1, 2) = true``` 的值，```pre[6]``` 存的是 ```[1, 6) = {true or} false and true = true``` 的值。
    
    那么不难发现，这个可以用前缀和的思想维护，即 ```pre[i] = pre[上一个 or 的位置] | (这一段 and 的值)```。
    
    ```上一个 or 的位置``` 我们可以开一个新数组 ```lastor[i]``` 维护 $i$ 上一个 ```or``` 的位置；```这一段 and 的值``` 则需要分类讨论：
      
      - $i-2$ 位置是 ```or```
      
        那么就是这种情况：```or (value) or```，那么 ```这一段 and 的值``` 就是这个 ```(value)```。
      
      - $i - 2$ 位置是 ```and```
      
        那就是这种情况：```or {(val) and ... and (val)} and (value) or```，此时 ```这一段 and 的值``` 就是 ```pre[i - 2] & (value)```（其中 ```pre[i - 2]``` 是花括号中的值）。
        
- 然后再是 ```suf[i]```：

  其实和 ```pre[i]``` 类似，只不过一个维护的是前缀，一个是后缀。反过来维护一遍就行了。
  
  还有，$i$ 位置下一个 ```or``` 的位置使用 ```nextor[i]``` 来存。这和 ```lastor[i]``` 一样下文有用。
  
以上的一大堆东西都是可以 $O(n)$ 预处理的。然后就可以 $O(1)$ 回答询问了：

首先，输入 $l,r$，还有一个 $\text{value}$。

那我们可以把序列分为 $5$ 部分：

```
l 前最近的 or 之前的部分 | l 前最近的 or 之后，在 l 之前的部分 & l 到 r 之间的部分 & 在 r 之后，r 后最近的 or 之前的部分 | r 后最近的 or 之后
```

其中，```[第三部分]``` 是你自己决定的 ```true/false```，而整个表达式的值就是 ```[第一部分] | [第二部分] & [第三部分] & [第四部分] | [第五部分]```。

用预处理的数组表示就是：

```pre[lastor[l]] | pre[l - 1] & (true/false) & suf[r + 1] | suf[nextor[r]]```

然后 ```(true/false)``` 用这两个值都代进去，看能不能有（至少）一个使表达式的值等于给定的 $\text{value}$ 就行了。如果可以输出 ```Y``` 否则输出 ```N```。

但是注意：**这五个部分不一定都存在，如果不存在就忽略掉，不要算**。

时间复杂度 $O(n)$。代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

string s;
char ch[N];
int n, m;
int pre[N], suf[N], lastor[N], nextor[N];

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i){
		cin >> s;
      //把这个字符串进行转化，后面比较好做
		if(s == "true") ch[i] = '1';
		if(s == "false") ch[i] = '0';
		if(s == "and") ch[i] = '&';
		if(s == "or") ch[i] = '|';
	}
	bool _pre = 0;
  //预处理前缀（可能跟讲的有点不一样，但是大差不差）
	for(int i = 1; i <= n; ++i){
		if(ch[i] == '1'){
			if(ch[i - 1] != '&') _pre = 1;
			else _pre = _pre & 1;
			pre[i] = _pre;
		}
		if(ch[i] == '0'){
			if(ch[i - 1] != '&') _pre = 0;
			else _pre = _pre & 0;
			pre[i] = _pre;
		}
		if(ch[i] == '&'){
			lastor[i] = lastor[i - 2];
			pre[i] = pre[i - 1];
		}
		if(ch[i] == '|'){
			pre[i] = pre[i - 1] | pre[lastor[i - 2]];
			lastor[i] = i;
		}
	}
	int _suf = 0;
  //后缀也做一遍预处理
	for(int i = n; i >= 1; --i){
		if(ch[i] == '1'){
			if(ch[i + 1] != '&') _suf = 1;
			else _suf = _suf & 1;
			suf[i] = _suf;
		}
		if(ch[i] == '0'){
			if(ch[i + 1] != '&') _suf = 0;
			else _suf = _suf & 0;
			suf[i] = _suf;
		}
		if(ch[i] == '&')
			nextor[i] = nextor[i + 2], suf[i] = suf[i + 1];
		if(ch[i] == '|')
			suf[i] = suf[i + 1] | suf[nextor[i + 2]], nextor[i] = i;
	}
  //处理询问
	for(int i = 1; i <= m; ++i){
		int l, r;
		bool now = 0;
		scanf("%d%d", &l, &r);
		cin >> s;
		if(s == "true") now = 1;
		else now = 0;
		bool _or1 = 0, _or2 = 1;
      //第一部分 | 第二部分 & (true/or) & 第四部分 | 第五部分
      //判断 第二部分 是否存在
		if(ch[l - 1] == '&') _or1 &= pre[l - 1], _or2 &= pre[l - 1];
      //判断 第四部分 是否存在
		if(ch[r + 1] == '&') _or1 &= suf[r + 1], _or2 &= suf[r + 1];
      //判断 第一部分 是否存在
		if(lastor[l - 1] != 0) _or1 |= pre[lastor[l - 1]], _or2 |= pre[lastor[l - 1]];
      //判断 第五部分 是否存在
		if(nextor[r + 1] != 0) _or1 |= suf[nextor[r + 1]], _or2 |= suf[nextor[r + 1]];
      //只要有一个满足就是 Y
		if(_or1 == now || _or2 == now) printf("Y");
		else printf("N");
	}
	return 0;
}
```

---

## 作者：returnzheng (赞：2)

首先，这道题如果暴力求解，复杂度就会直线飙升。所以需要寻找其它方法。

经过观察发现，这道题要替换中间的值，可以用一种类似前缀后缀和的思路预处理出左边的值和右边的值。把原式按 or 分成很多块，求解出前缀的所有 or 块的结果，后缀所有 or 块的结果，当前块中前缀 and 的结果和当前块中后缀 and 的结果，就可以把中间一块替换后轻松求解出结果。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
char c[300000];
int and1[300000];
int and2[300000];
int or1[300000];
int or2[300000];
int main(){
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++){
        string s;
        cin >> s;
        if (s == "true"){
            c[i] = '1';
        }
        if (s == "false"){
            c[i] = '0';
        }
        if (s == "and"){
            c[i] = '&';
        }
        if (s == "or"){
            c[i] = '|';
        }
    }
    and1[1] = 1;
    or1[1] = 0;
    for (int i = 3; i <= n; i += 2){
        if (c[i - 1] == '&'){
            and1[i] = and1[i - 2] & (c[i - 2] - '0');
            or1[i] = or1[i - 2];
        }
        else{
            and1[i] = 1;
            or1[i] = or1[i - 2] | (and1[i - 2] & (c[i - 2] - '0'));
        }
    }
    and2[n] = 1;
    or2[n] = 0;
    for (int i = n - 2; i >= 1; i -= 2){
        if (c[i + 1] == '&'){
            and2[i] = and2[i + 2] & (c[i + 2] - '0');
            or2[i] = or2[i + 2];
        }
        else{
            and2[i] = 1;
            or2[i] = or2[i + 2] | (and2[i + 2] & (c[i + 2] - '0'));
        }
    }
    while (q--){
        int l, r;
        cin >> l >> r;
        string s;
        cin >> s;
        int op = (s == "true");
        if ((or1[l] | (and1[l] & true & and2[r]) | or2[r]) == op || (or1[l] | (and1[l] & false & and2[r]) | or2[r]) == op){//把式子分成完全没有替换的块，替换了一部分的块以及替换的内容，代入求解。
            cout << "Y";
        }
        else{
            cout << "N";
        }
    }
    cout << '\n';
    // for (int i = 1; i <= n; i += 2){
    //     cout << i << " : " << or1[i] << " " << and1[i] << " " << or2[i] << " " << and2[i] << '\n';
    // }
    return 0;
}
```

---

## 作者：haozige (赞：2)

# P10274 Logical Moos

[题目传送门](https://www.luogu.com.cn/problem/P10274)

## 题意概括

给你一个长度为 $N$ 的布尔语句，其中包含 $\texttt{true}$、$\texttt{false}$、$\texttt{and}$ 和 $\texttt{or}$，其含义与原来相同，已保证这个布尔语句一定是合法的，给你 $Q$ 次查询，每次查询你可以替换第 $l$ 个到第 $r$ 个的段为 $\texttt{true}$ 或 $\texttt{false}$，然后询问是否能得到 FJ 想要的布尔值（布尔语句计算方式与原来一样，优先算 $\texttt{and}$，然后再算 $\texttt{or}$）。

## 思路

这道题处理方式相比这次公开赛的其他铜组的题目略显复杂，~~本人肯定不是最优解，这是我比赛的时候想出来的~~，首先看到 $1\le Q\le 2\cdot 10^5$ 就可以知道这里的预处理必须多一点的，所以我做的时候先处理了所有单独的 $\texttt{and}$ 串，因为对于每个只由 $\texttt{and}$ 连接起来的 $\texttt{and}$ 串，其实是一个整体，然后处理好了每个 $\texttt{and}$ 串的结果之后就只剩 $\texttt{or}$ 了，我们为了达到更低的时间复杂度，也因为只剩 $\texttt{or}$ 没处理了，直接把它以 前缀和 和 后缀和 的形式处理好，但是还有个问题，就是替换的时候可能会把 $\texttt{and}$ 串截断，所以对于每个小的 $\texttt{and}$ 串，还要在里面判断好这个 $\texttt{and}$ 串内，每个位置之前有没有 $\texttt{false}$（一旦有，就说明这个 $\texttt{and}$ 串无论怎样结果都是 $\texttt{false}$），最后每次查询就可以用之前的处理好的数组得出结果了，最终可以分为四个部分：$\texttt{and}$ 串处理、$\texttt{or}$ 的 前缀后缀和 处理，$\texttt{and}$ 串内部的预处理、查询与计算。

### 第一部分：$\texttt{and}$ 串处理

第一部分的处理我是和输入一起写的，在输入的过程中，我们可以把它当做遍历过程，对于奇数位，我们要判断他是 $\texttt{true}$ 还是 $\texttt{false}$，若是 $\texttt{true}$，则在这一段的结果不变，判断一下这一段结果记录过没，没记录过赋值 $\texttt{true}$，若是 $\texttt{false}$，这一段连续的 $\texttt{and}$ 串的结果变为 $\texttt{false}$，因为对于每个 $\texttt{and}$ 串，他们中间是只有 $\texttt{and}$ 没有 $\texttt{or}$ 的，也就意味着一旦中间有 $\texttt{false}$，整个 $\texttt{and}$ 串的结果就一定是 $\texttt{false}$，对于偶数位，我们要判断它是 $\texttt{and}$ 还是 $\texttt{or}$，若是 $\texttt{and}$，说明在 $\texttt{and}$ 串之中，不用处理，若是 $\texttt{or}$，这意味着前一个 $\texttt{and}$ 串的结束和下一个 $\texttt{and}$ 串的开始，所以记录下前一个 $\texttt{and}$ 串的结束位置和下一个 $\texttt{and}$ 串的开始位置，这里还会建立一个 $cnt$ 变量，统计 $\texttt{and}$ 串个数，之后用的到，然后别忘了开头和结尾的边界情况要再处理一下，还要再建立一个数组再标记一下每个位所在第几个 $\texttt{and}$ 串（也用得上）。

### 第二部分：$\texttt{or}$ 的 前缀后缀和 处理

第二部分我们先写前缀的处理（因为后缀是一样的，倒着再写一遍就好了），先把第一个前缀和的值处理好，然后就用的到前文的 $cnt$ 了，这里遍历每个 $\texttt{and}$ 串，先赋值为上一个的值，再判断这个 $\texttt{and}$ 串的结果是 $\texttt{true}$ 还是 $\texttt{false}$，若是 $\texttt{true}$，变为 $\texttt{true}$，因为这里只由 $\texttt{or}$ 连接了，一旦有一个 $\texttt{true}$，结果就是 $\texttt{true}$，若是 $\texttt{false}$，则结果不变，然后再倒着写一遍后缀就解决了。

### 第三部分：$\texttt{and}$ 串内部的预处理

第三部分的处理也先写前缀，同样的后缀也是一样的倒过来写一遍，用 $cnt$ 遍历每个 $\texttt{and}$ 串，这样方便计算这个 $\texttt{and}$ 串之内，每个位置前是否有 $\texttt{false}$，在每个 $\texttt{and}$ 串里面再遍历每个位置，判断每个位置的值，如果是 $\texttt{false}$就标记下，然后使用这个标记来判断每个位置前是否有 $\texttt{false}$。

### 第四部分：查询与计算

最后是有点麻烦的第四部分，首先要把几种特殊情况去掉，就是左节点和右节点在边界的，如果两遍都占直接输出 `Y` 就行，因为无论怎样肯定可以，只占一边的直接统计另一边结果就好了，但其实还有种特殊情况就是两个节点任意一个在边界的 $\texttt{and}$ 串里的，这个好处理一点，单独判断就行，剩下的就是正常情况了。

我这里分成了三段来写第一段是左节点所在的 $\texttt{and}$ 串的前面，就是用前面第二个处理的东西来判断前部分结果，第二段是改变段在的 $\texttt{and}$ 串，这里就用第三个处理的东西，第三段是右节点所在的 $\texttt{and}$ 串的后面，这里和第一段一样，倒过来而已，最后把三段结合一下，就能得到答案。

## 代码

这是最后的代码，时间复杂度 $O(4n+2cnt+Q)$：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,key[200005],_or[200005],or_[200005],_key_[200005],_key_or[200005],key_or[200005];
int cnt=1;
struct and_{
	int fa,start,finish;
}_and_[200005];
void slove(){
	int l,r,f,ans;
	string s;
	cin>>l>>r>>s;
	f=s=="false"?0:1;
	if(l==1&&r==n){
		cout<<"Y";
		return;
	}
	if(l==1){
		if(key_or[r]==-1){
			if(or_[_key_[r]+1]==0) ans=-1;
			else ans=1;
		}else{
			if(or_[_key_[r]+1]==0) ans=2;
			else ans=1;
		}
	}else if(r==n){
		if(_key_or[l]==-1){
			if(_or[_key_[l]-1]==0) ans=-1;
			else ans=1;
		}else{
			if(_or[_key_[l]-1]==0) ans=2;
			else ans=1;
		}
	}else{
		int lf=0,mf=0,rf=0;
		if(_key_or[l]==-1||key_or[r]==-1) mf=-1;
		else mf=2;
		if(_key_[l]-1>0){
			if(_or[_key_[l]-1]==0) lf=-1;
			else lf=1;
		}
		if(_key_[r]+1<=cnt){
			if(or_[_key_[r]+1]==0) rf=-1;
			else rf=1;
		}
		if(lf==0&&rf==0) ans=mf;
		else if(lf==0){
			if(rf==1) ans=1;
			else{
				if(mf==2) ans=2;
				else ans=-1;
			}
		}else if(rf==0){
			if(lf==1) ans=1;
			else{
				if(mf==2) ans=2;
				else ans=-1;
			}
		}else{
			if(rf==1||lf==1) ans=1;
			else{
				if(mf==2) ans=2;
				else ans=-1;
			}
		}
	}
	if(ans==2){
		cout<<"Y";
	}else if(ans==-1){
		if(f==0) cout<<"Y";
		else cout<<"N";
	}else{
		if(f==1) cout<<"Y";
		else cout<<"N";
	}
	return;
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		if(s=="false"){
			key[i]=0;
			_and_[cnt].fa=-1;
		}
		else if(s=="true"){
			key[i]=1;
			if(_and_[cnt].fa!=-1) _and_[cnt].fa=1;
		}
		else if(s=="and"){
			key[i]=2;
		}
		else{
			key[i]=3;
			_and_[cnt].finish=i-1;
			cnt++;
			_and_[cnt].start=i+1;
		}
	}
	_and_[1].start=1;
	_and_[cnt].finish=n;
	for(int i=1;i<=cnt;i++){
		for(int j=_and_[i].start;j<=_and_[i].finish;j++){
			_key_[j]=i;
		}
	}
	_or[1]=_and_[1].fa==-1?0:1;
	for(int i=2;i<=cnt;i++){
		_or[i]=_or[i-1];
		if(_and_[i].fa==1) _or[i]=1;
	}
	or_[cnt]=_and_[cnt].fa==-1?0:1;
	for(int i=cnt-1;i>=1;i--){
		or_[i]=or_[i+1];
		if(_and_[i].fa==1) or_[i]=1;
	}
	for(int i=1;i<=cnt;i++){
		int or_t=0;
		for(int j=_and_[i].start;j<=_and_[i].finish;j++){
			if(or_t==1){
				_key_or[j]=-1;
				continue; 
			}
			if(key[j]==0){
				or_t=1;
			}
		}
	}
	for(int i=cnt;i>=1;i--){
		int or_t=0;
		for(int j=_and_[i].finish;j>=_and_[i].start;j--){
			if(or_t==1){
				key_or[j]=-1;
				continue; 
			}
			if(key[j]==0){
				or_t=1;
			}
		}
	}
	for(int i=1;i<=q;i++) slove();
    return 0;
}
```

---

## 作者：wqc2011 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10274)

### 题意
给你一个运算语句，若更改其中一段的值，询问能否得到指定的答案？
### 思路
如果考虑暴力求解，不仅十分麻烦，还会超时。先观察一下样例：
```cpp
13 4
false or true and false and false and true or true and false
// 此语句可表示为：
// 0 | 1 & 0 & 1 & 1 | 1 & 0
// 其中，我们需要先进行与运算，再进行或运算，即可表示为
// 0 | (1 & 0 & 1 & 1) | (1 & 0)
// 0 | 0 | 0
// 0
``` 
我们发现，若先处理完所有与的值，原式会变为如下状态：

```cpp
// ... or ... or .. or ...
```
#### 预处理
考虑或值的前缀 $or_i$ 的值时，只需考虑前一个 $or_{i-1}$ 的值或上两个 $\text{or}$ 之间的与值 $and_i$ 即可，后缀同理。

在考虑与值的前缀 $add_i$ 时，只需考虑从上一个 $\text{or}$ 到 $i$ 的值，因为每一个 $\text{or}$ 会把 $\text{and}$ 分割开，我们只需考虑每两个 $\text{or}$ 之间的与值即可，$and_i$ 的值即为 $and_{i-1} \operatorname{and} a_i$，注意在 $s_i$ 为 $\text{or}$ 时，我们令 $and_i$ 为 $true$，后缀同理。

注意，所有的 $i$ 均为偶数，因为我们只用考虑 $\text{and}$ 和 $\text{or}$ 的位置上的前缀与后缀即可，因为考虑数值位是无意义的。

最后求出答案时，就可以 $O(1)$ 求解。

所以，我们可以预处理出 $and$ 和 $or$ 的前缀与后缀。前缀转移如下：


```
// 看一下例子：
// 0 | 1 & 0 & 1 & 1 | 1 & 0
// 0 | (1 & 0 & 1 & 1) | (1 & 0)
//        ^ 现在处理到此位
// 在当前位置是与时：
// 从 上一个 or 的位置推导至当前位置的与值为从 i - 2 的位置的值与上 i - 1 位置上 and 前缀的值
// 0 | (1 & 0 & 1 & 1) | (1 & 0)
//   ^  ^ 这两个位置相与
// 此时的或值为上一个或的位置的值（不受当前位置值的影响）
add1[0] = 1;
for(int i = 2;i <= n + 1;i += 2){
    if(op[i]=="and"){//如果当前位置是与
        add1[i] = add1[i - 2] & a[i - 1];
        orr1[i] = orr1[i - 2];
    }else{//当前位置是或
        add1[i] = 1;
        orr1[i] = (a[i - 1] & add1[i - 2]) | orr1[i - 2];
    }
}
// 0 | 1 & 0 & 1 & 1 | 1 & 0
// 0 | (1 & 0 & 1 & 1) | (1 & 0)
//                     ^ 现在处理到此位
// 由于前面的与值对这一位没有影响，所以 and 前缀的值直接赋true
// true与上任何数都没有影响
// or 的前缀为 从上一个 or 至当前位置的与值 或上 上一个 or 的前缀
// 0 | (1 & 0 & 1 & 1) | (1 & 0)
//                ^ ^
// 先把这两个与起来（这是前面一段与的值）
// 0 | (1 & 0 & 1 & 1) | (1 & 0)
//   ^
// 再或上这个（这是再往前所有的值）
```
后缀处理同理。
#### 计算答案
处理完后就准备输出答案了。

```
// 例子：
13 4
false or true and false and false and true or true and false
1 5 false
3 11 true
// 0 | 1 & 0 & 1 & 1 | 1 & 0
// ^        ^  
// 修改 1 至 5 之间的值
// 用改后的值先于上 and 的前缀 l - 1 与 and 的后缀 r + 1
// 再或上 or 的前缀 l -1 与 or 的后缀 r + 1
// 最后看大案符不符合标准即可
bool p = 0;
bool ans1 = (((p & add1[l - 1]) & add2[r + 1]) | orr1[l - 1]) | orr2[r + 1];
p = 1;
bool ans2 = (((p & add1[l - 1]) & add2[r + 1]) | orr1[l - 1]) | orr2[r + 1];
if(ans1 == ans || ans2 == ans){
    cout << 'Y';
}else{
    cout << 'N';
}
```
### 代码附上——

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 200010;
const int inf = 1e9;
//unsigned long long 
//cout << fixed << setprecision(3)
//cout << setw(5) << 
//continue
bool a[maxn], op[maxn];
bool orr1[maxn], orr2[maxn], add1[maxn], add2[maxn];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        string s;
        cin >> s;
        if(s == "true"){
            a[i] = 1;
        }else if(s == "and"){
            op[i] = 1;
        }
    }
    add1[0] = 1;
    for(int i = 2;i <= n + 1;i += 2){
        if(op[i]){
            add1[i] = add1[i - 2] & a[i - 1];
            orr1[i] = orr1[i - 2];
        }else{
            add1[i] = 1;
            orr1[i] = (a[i - 1] & add1[i - 2]) | orr1[i - 2];
        }
    }
    add2[n + 1] = 1;
    for(int i = n - 1;i >= 0;i -= 2){
        if(op[i]){
            add2[i] = add2[i + 2] & a[i + 1];
            orr2[i] = orr2[i + 2];
        }else{
            add2[i] = 1;
            orr2[i] = (a[i + 1] & add2[i + 2]) | orr2[i + 2];
        }
    }
    for(int i = 1;i <= m;i++){
        int l, r;
        bool ans = 0;
        string s;
        cin >> l >> r >> s;
        if(s == "true") ans = 1;
        bool p = 0;
        bool ans1 = (((p & add1[l - 1]) & add2[r + 1]) | orr1[l - 1]) | orr2[r + 1];
        p = 1;
        bool ans2 = (((p & add1[l - 1]) & add2[r + 1]) | orr1[l - 1]) | orr2[r + 1];
        if(ans1 == ans || ans2 == ans){
            cout << 'Y';
        }else{
            cout << 'N';
        }
    }
    return 0;
}
```
感谢阅读！

---

## 作者：int_4096 (赞：0)

[传送门](https://www.luogu.com.cn/problem/P10274)

### 题意简述
给出一个 `bool` 运算串，给出一段区间（端点一定为 `bool` 值），可以将其修改为 `true` 或 `false`，问能否得到给定值。 
### 分析
容易想到可以求前缀后缀，但是问题在于 `and` 优先级更高，不能简单地将前后的值拼起来。

因为 `and` 优先级更高，我们把连续的 `and` 运算视为一个 `and` 块。  
我们考虑，当前后出现任意一个 `or + true` 的组合后（`true` 包括由 `and` 块得到的），表达式一定为真。若没有，则说明现在值取决于中间的 `and` 块。  
因此我们考虑记录前缀与后缀的值（直接求值，即后面代码的 `pre_or` 与 `suf_or`）和向前与向后的 `and` 块值。
### 做法
当 `pre_or` 或 `suf_or` 为真时，表达式一定为真。  
否则查询中间所在的 `and` 块，如果向前向后都为真，则区间填 `true` 值为真，取 `false` 值为假。   
否则表达式一定为假。
### Code
```cpp
#include <cstdio>
#include <algorithm>
typedef long long ll;
const int N = 200005;
int n, q;
enum Operator {
	False, True, And, Or
}; // 可以写为 const int False = 0, True = 1, And = 2, Or = 3;
int a[N];
char s[15];
int pre_or[N], suf_or[N]; // 向前/向后的值
int pre_and[N], suf_and[N]; // 向前/向后的 and 块的值
int pra[N], sfa[N]; // 记录向前/向后的 and 块最远的的位置
int main() {
	//qwq
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s);
		if (*s == 'a') a[i] = And;
		else if (*s == 'o') a[i] = Or;
		else if (*s == 't') a[i] = True;
		else a[i] = False;
	}
	for (int i = 1; i <= n; i += 2) {
		pre_and[i] = a[i], pra[i] = i; // 这个位置的值
		if (i != 1 && a[i - 1] == And) // 如果中间是 and (即与上一个相连)
			pre_and[i] &= pre_and[i - 2], pra[i] = pra[i - 2]; // 取 &= 并改 pra
	}
	for (int i = n; i >= 1; i -= 2) {
		suf_and[i] = a[i], sfa[i] = i;
		if (i != n && a[i + 1] == And)
			suf_and[i] &= suf_and[i + 2], sfa[i] = sfa[i + 2];
	} // 同上
	for (int i = 1; i <= n; i += 2) {
		pre_or[i] = pre_and[i];
		if (pra[i] != 1)
			pre_or[i] |= pre_or[pra[i] - 2]; // 这个 and 块与之前的值或起来 (即求值)
	}
	for (int i = n; i >= 1; i -= 2) {
		suf_or[i] = suf_and[i];
		if (sfa[i] != n)
			suf_or[i] |= suf_or[sfa[i] + 2]; // 同上
	}
	for (int rep = 1, l, r; rep <= q; rep++) {
		scanf("%d%d %s", &l, &r, s);
		int pre = 0, preA = (l == 1 ? 1 : pre_and[l - 2]);
		int suf = 0, sufA = (r == n ? 1 : suf_and[r + 2]);
		// pre, suf 为值 (即判断是否有 or + true)

		// preA, sufA 为中间所在的 and 块的前缀和后缀
		// 中间形如 (...) or A and B and __ and C and D or (...)
		// preA = A and B; sufA = C and D
		if (pra[l] - 2 >= 1)
			pre = pre_or[pra[l] - 2];
		if (sfa[r] + 2 <= n)
			suf = suf_or[sfa[r] + 2];
		preA |= (a[l - 1] == Or); // 当左右算符为 or 时，视为 true (显然)
		sufA |= (a[r + 1] == Or);
		if (pre || suf) // 一定为真
			putchar(*s == 't' ? 'Y' : 'N');
		else if (preA && sufA) // 填进去啥就是啥
			putchar('Y');
		else putchar(*s == 'f' ? 'Y' : 'N'); // 一定为假
	}
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
有一串 $n$ 个元素的逻辑运算（只有与和或），单数个元素是数值，偶数个，$q$ 组询问问你将从 $l$ 到 $r$ 全都替换成一个 $1$ 或 $0$（任选其一），问最后的结果可不可能是给定的求值结果。
## 大体思路
这道题其实写起来不是那么容易，而且需要注意的地方也有很多，像一个非常大模拟。

概括来讲，我们先维护一个前缀答案和后缀答案，然后再算”与块“的前端点和后端点，以及每个"与块"从前往后以及从后往前一直到当前节点的值有没有可能是真，注意与和或的运算先后顺序。

我们下面来具体看一下。

### 维护前后缀
我们可以维护一个栈和一个值 $sfs1$ 配合来做，栈就是模拟逻辑运算操作，里面只存元素，如果是或运算，那么直接把两个元素放进去，如果是与运算，把两个栈顶取出来与运算一下再放进去，那么一直运算到现在的值就是栈里面所有值或起来。

为了预防后面可能出现的与运算，$sfs1$ 存不计算当前值的答案，这样每次我们只需要把当前前缀赋值为 $sfs1\lor sta[tot]$ 即可。

后缀同理。

这样就算有与运算连接下一位，栈里面可以正常存，$sfs1$ 无影响，由于存的是不计算当前值的答案，所以我们只需要再或一下当前值就可以。（仔细想一想，理解一下）
### “与块”
我们会发现我们删除的区间左右可能连接着外面的几个与运算，由于与运算优先级更高，所以我们需要预处理所有"与块"的值有没有可能是真值，如果是，那么可以得到真值，如果不是，那么只能得到假值。

我们可以再前面维护前后缀的时候直接处理与块，具体的，我们也像前后缀一样要从前往后、从后往前都跑一边，维护“与块”$a$，变量 $zhi$、$sum$、$qor$、$hor$，分别表示整个“与块”遍历到现在的值是真是假；遍历到现在“与块”中元素 $0$ 的个数；从当前点往左数第一个或的位置（记录其连接的第一个元素）；从当前点往右数第一个或的位置（记录其连接的第一个元素。

每个“与块”，维护 $l,r,cl,cr$，分别表示当前值连起来的“与块”的左端点的前一个元素、右端点的后一个元素（存”前一个“和”后一个“便于我们在处理询问时直接带前后缀）、往左走可不可能都是真值，往右走可不可能都是真值。

具体要怎么做呢？在记录上面所有值的前提下，从前往后从后往前都遍历一遍，一次确定左端点和在当前”与块“一直往左走能不能全是真值，另一次确定右端点和在当前”与块“一直往右走能不能全是真值。
### 处理询问
该维护的我们都维护好了，怎么使用他们呢？

我们每次询问得到了一个左节点 $l$ 和右节点 $r$，和所期盼的最后结果的值。

我们考虑这四个值：$qz[a[l]_l]$、$a[l]_{cl}$、$a[r]_{cr}$、$hz[a[r]_r]$。

注意到如果我们期盼一个假值，那么"与块"中能且最好取到假值。

所以说若我们期盼一个假值，我们就判断 `qz[a[l].l]|hz[a[r].r]` 是否为假值，是就输出 `Y`，不是就输出 `N`。

若我们期盼一个真值，我们就判断 `qz[a[l].l]|(a[l].cl&a[r].cr)|hz[a[r].r]` 是否为真值，是就输出 `Y`，不是就输出 `N`。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int l,r,cl=1,cr=1;//和当前值连起来的“与块”的左端点的前一个元素、右端点的后一个元素、往左走可不可能都是真值，往右走可不可能都是真值 
}a[500005];
int all[500005];
int qz[500005],hz[500005];
int sta[500005],tot;
string s;
bool sfs1;
int main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>s;
		if(s[0]=='f'){
			all[i]=0;
		}
		if(s[0]=='t'){
			all[i]=1;
		}
		if(s[0]=='a'){
			all[i]=2;
		}
		if(s[0]=='o'){
			all[i]=3;
		}//全都变成可读性良好的数据（） 
		a[i].l=max(0,i-2);
		a[i].r=min(n+1,i+2);//初始化为自己的上一个和下一个 
	}
	int zhi=1;//整个“与块”遍历到现在的值是真是假 
	int sum=0;//“与块”中元素 0 的个数 
	int qor=0;//从当前点往左数第一个或的位置（记录其连接的第一个元素），初始化为 0，因为我们定义qz[0]=0。 
	a[1].l=0;
	for(int i=1;i<=n;i+=2){//直接每次 +2 即可，免得麻烦 
		sta[++tot]=all[i];//维护这个栈 
		if(all[i-1]==3||i==1){//特判如果运算符是或运算或者是第一个遍历的点 
			qor=i-2;//更新这个或运算的位置 
			zhi=all[i];//更新遍历到现在的“与块”的值 
			sum=(all[i]==0);//如果当前是假值，假值个数加一 
		}
		if(all[i-1]==2){
			int cz1=sta[tot],cz2=sta[tot-1];//维护栈 
			sta[tot-1]=(cz1&cz2);
			tot--;
			zhi&=all[i];
			if(all[i]==0){//“与块”的第一个点前面肯定不是与运算，进不来 
				sum++;
			}//是零加一 
			if(!(sum-(all[i]==0))){//如果遍历到除了当前的点全是真值 
				a[i].cl=1;//整个“与块”往左走可以全是真值 
			}
			else{
				a[i].cl=0;
			}//维护“与块”
			a[i].l=qor;//赋值为左端点 
		}
		if(tot-1>0){//维护前缀 
			sfs1|=sta[tot-1];
		}
		qz[i]=sfs1|sta[tot];
	}
	int hor=n+1;//从当前点往右数第一个或的位置，初始化为 n+1，因为我们定义hz[n+1]=0。 
	zhi=1;
	tot=0;
	sfs1=0;
	sum=0;//记得清空 
	a[n].r=n+1;
	for(int i=n;i>=1;i-=2){
		sta[++tot]=all[i];//维护这个栈 
		if(all[i+1]==3||i==n){//特判如果运算符是或运算或者是第一个遍历的点 
			hor=i+2;//更新这个或运算的位置 
			zhi=all[i];//更新遍历到现在的“与块”的值 
			sum=(all[i]==0);//如果当前是假值，假值个数加一 
		}
		if(all[i+1]==2){
			int cz1=sta[tot],cz2=sta[tot-1];
			sta[tot-1]=(cz1&cz2);
			tot--;//维护栈 
			zhi&=all[i];
			if(all[i]==0){
				sum++;
			}
			if(!(sum-(all[i]==0))){
				a[i].cr=1;//整个“与块”往右走可以全是真值 
			}
			else{
				a[i].cr=0;
			}
			//维护“与块”
			a[i].r=hor;//赋值为左端点 
		}
		if(tot-1>0){//维护前缀 
			sfs1|=sta[tot-1];
		}
		hz[i]=sfs1|sta[tot];
	}
	tot=0;
	sfs1=0;
	qz[0]=0;
	hz[n+1]=0;
	for(int i=1;i<=q;i++){
		int l,r;
		cin>>l>>r>>s;
		int z;
		if(s[0]=='f'){
			z=0;
		}
		else{
			z=1;
		}
		if(z==0){//处理询问 
			int h=qz[a[l].l]|hz[a[r].r];
			if(h==0){
				putchar('Y');
			}
			else{
				putchar('N');
			}
		}
		else{
			int h=qz[a[l].l]|(a[l].cl&a[r].cr)|hz[a[r].r]; 
			if(h==0){
				putchar('N');
			}
			else{
				putchar('Y');
			}
		}
	}
	return 0;
}
```

---


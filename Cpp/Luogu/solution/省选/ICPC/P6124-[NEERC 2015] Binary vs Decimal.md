# [NEERC 2015] Binary vs Decimal

## 题目描述

一个正数 $A$，如果它只包含 `0` 或 `1`，且它转成二进制后的 $B$，$A$ 是 $B$ 的后缀，这个数就是我们所要的。

现在给出数字 $N$，求第 $N$ 个这样的数。

## 说明/提示

$1 \le N \le 10^4$。

|原数|二进制|评论|
| :-----------: | :-----------: | :-----------: |
|$1$|$1$|√|
|$10$|$1010$|√|
|$11$|$1011$|√|
|$100$|$1100100$|√|
|$101$|$1100101$|√|
|$110$|$1101110$|√|
|$111$|$1101111$|√|
|$1000$|$1111101000$|√|
|$1001$|$1111101001$|√|
|$1010$|$1111110010$|×|
|$1011$|$1111110011$|×|
|$1100$|$10001001100$|√| 

## 样例 #1

### 输入

```
2```

### 输出

```
10```

## 样例 #2

### 输入

```
10```

### 输出

```
1100```

# 题解

## 作者：_xuyimeng_ (赞：6)

## 分析  
打个表或者通过直觉不难发现：新的数要在已有符合条件数的前面加1构造得到。因为10=5*2，在前面加数才能保证后面十进制和二进制的关系不被破坏。

我们考虑取出一个已经符合条件的数在前面添上1进行更新：  

**十进制:** $\overline{A}(i位)+\overline{100...0}(i位0)=\overline{1A}$  
**二进制:** $\overline{XA}(i位)+\overline{Y0...00}(i位0)=\overline{ZA}$  
因为$10^i=5^i\times2^i$，所以$Y\&1=1$，十进制为二进制后缀当且仅当$X\&1=0$，即$(A>>i)\&1=0$，此时将$A$计入答案即可  
否则，$(A>>i)\&1=1$，当前这个数$A$就不能通过$+10^k(k>i)$构造出新的合法数了。因为$A+10^k$十进制下第i位为$0($因为$i<k)$，二进制下$A$第$i$位为$1($即$(A>>i)\&1=1)$，$10^k$第$i$位为$0($同上$)$，相加得$1$，不可能成立，标记一下，下次枚举到时跳过即可。

总体复杂度$O(nl)$
## 代码实现  
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=10003;
int n,m=1,M,f[N];//f[i]:上文提到的标记第i个答案是否能够生成新的答案
struct Bigint {//高精
	int len;
	vector <int> num;
	Bigint()=default;
	void clear(int size) {
		num.clear();
		num.resize(size+1);
		len=size;
	}
}d[N],p,tmp;
//d[i]:第i个符合要求的数
Bigint Bigint_add(const Bigint &a, const Bigint &b) {//高精加高精  
	Bigint res;
	res.clear(max(a.len,b.len)+1);
	for(int i=1; i<res.len; i++) {
		res.num[i]+=(i<=a.len?a.num[i]:0)+(i<=b.len?b.num[i]:0);
		if(res.num[i]>=10) {
			res.num[i+1]+=res.num[i]/10;
			res.num[i]%=10;
		}
	}
	while(res.len>1&&res.num[res.len]==0) res.len--, res.num.pop_back();
	return res;
}
Bigint Bigint_div2(Bigint a) {//高精右移操作  
	for(int i=a.len; i>=1; i--) {
		if(a.num[i]&1) a.num[i-1]+=10;
		a.num[i]>>=1;
	}
	if(a.len>1&&a.num[a.len]==0) a.len--, a.num.pop_back();
	return a;
}
Bigint Bigint_upd(const Bigint &a) {//更新p 相当于乘10
	Bigint res;
	res.clear(a.len+1);
	for(int i=1;i<res.len;i++) res.num[i]=0;
	res.num[res.len]=1;
	return res;
}
void print(const Bigint &a) {//高精输出
	for(int i=a.len;i>=1;i--) printf("%d",a.num[i]);
	return;
}
int main() {
	scanf("%d",&n);
	d[0].clear(1); d[0].num[1]=0;//0不计入总数 但可以用于更新
	d[1].clear(1); d[1].num[1]=1;
	p.clear(1); p.num[1]=1;
	for(int i=1;m<n;i++) {
		p=Bigint_upd(p);
		M=m;
		for(int j=0;j<=M;j++) {
			if(f[j]) continue;
			tmp=d[j];
			for(int k=1;k<=i;k++) tmp=Bigint_div2(tmp);//右移i位
			if(tmp.num[1]&1) f[j]=1;
			else {
				d[++m]=Bigint_add(d[j],p);
				if(m==n) break;
			}
		}
	}
	print(d[m]);
	return 0;
}
```
我知道我排版很丑 语言表达也很烂 不要喷我qwq

---

## 作者：BreakPlus (赞：4)

一道不错的 BFS 题目。

我们在队列里先加入 $0$ 和 $1$，然后对于队列中的每个数从低位向高位搜起，接下来我们聊一聊怎么搜。

如果当前的数是 $k-1$ 位，那么在它前面加 $1$ 显然需要加上 $10^k$（加  $0$ 不用说，因为大小不变）。

因为 $10$ 的二进制末尾有个 $0$ ，那么 $10^k$ 的二进制末尾也至少有 $k$ 个 $0$。

这样一来，给当前的数加上 $10^k$，后面的 $k-1$ 位完全没有变化，只需要在前面添上一些数就好了（懒得具体写了，自行理解应该不难吧 qaq）。

于是这题就讲解完了。

P.S. 貌似不需要剪枝优化，没卵用，搜到第 $n$ 个数才是王道。

P.P.S. 毒瘤高精，窝用了python，以后用空可能会写个 [C++ 版本](https://www.luogu.com.cn/paste/cvrtdt0a) 的代码，毕竟 CCF 不给用 Py 啊。

代码：

```python
n=input()
n=int(n) #读入 n
lists=[] #BFS 队列
cd=[] #长(c)度(d)
def start():
    lists.append(0)
    lists.append(1)
    cd.append(1)
    cd.append(1)
start()#初始化
now_len=0#当前长度
now_ten=10#当前10^k
while len(lists)<=n:
    now_len+=1
    temp_len=len(lists)
    for east in range(len(lists)):
        if (lists[east]>>cd[east])&((1<<(1+now_len-cd[east]))-1)==0:
            lists.append(lists[east]+now_ten)
            cd.append(now_len+1)#整个 BFS 过程
    now_ten*=10
print (lists[n]) #华丽地结束
```

---

## 作者：_YyD_ (赞：4)

**题目大意：**

一个正数 $A$，如果它只包含 0 或 1，且它转成二进制后的 $B$，$A$ 是 $B$ 的后缀，这个数就是我们所要的。

现在给出数字 $N$，求第 $N$ 个这样的数

**思路：**

对于一个合法的十进制数，它的所有后缀也是合法的。

于是按位 BFS，保留前导零,每次往前添加一个 $0$ 或者 $1$，直到找到第 $n$ 个不含前导零的合法数为止即可。

时间复杂度为 $O(nl)$。


```cpp
#include<cstdio>
#define N 400
struct Num{
  int len,v[N];
  Num(){for(int i=len=1;i<N;i++)v[i]=0;}
  Num operator+(const Num&b){
    Num c;
    c.len=b.len+1;
    for(int i=1;i<=c.len;i++)c.v[i]=v[i]+b.v[i];
    for(int i=1;i<=c.len;i++)c.v[i+1]+=c.v[i]>>1,c.v[i]&=1;
    while(!c.v[c.len])c.len--;
    return c;
  }
  Num operator*(const Num&b){
    Num c;
    c.len=len+b.len;
    for(int i=1;i<=len;i++)for(int j=1;j<=b.len;j++){
      if(i+j-1>=N)break;
      c.v[i+j-1]+=v[i]*b.v[j];
    }
    for(int i=1;i<=c.len;i++)c.v[i+1]+=c.v[i]>>1,c.v[i]&=1;
    while(!c.v[c.len])c.len--;
    return c;
  }
}Ten,Pow,y;
struct Big{int len,v[N];Big(){len=0;for(int i=1;i<N;i++)v[i]=0;}}x;
struct P{Big x;Num y;P(){}P(Big _x,Num _y){x=_x,y=_y;}}q0[2][210],q1[2][210];
int t0[2],t1[2],n,i,j,k,o;
inline bool check(int x,Big d,Num b){
  for(int i=1;i<=x;i++)if((i<=d.len?d.v[i]:0)!=(i<=b.len?b.v[i]:0))return 0;
  return 1;
}
int main(){
  Ten.v[2]=Ten.v[4]=1,Ten.len=4;
  Pow.v[1]=1;
  scanf("%d",&n);
  q0[0][t0[0]=1]=P(Big(),Num());
  for(i=1;;i++,o^=1,Pow=Pow*Ten){
    t0[o^1]=t1[o^1]=0;
    for(j=1;j<=t0[o];j++){
      x=q0[o][j].x,y=q0[o][j].y;
      if(check(i,x,y))q0[o^1][++t0[o^1]]=P(x,y);
      x.len=i,x.v[i]=1,y=y+Pow;
      if(check(i,x,y)){
        if(!(--n)){
          for(k=i;k;k--)putchar(x.v[k]+'0');
          return 0;
        }
        q1[o^1][++t1[o^1]]=P(x,y);
      }
    }
    for(j=1;j<=t1[o];j++){
      x=q1[o][j].x,y=q1[o][j].y;
      if(check(i,x,y))q0[o^1][++t0[o^1]]=P(x,y);
      x.len=i,x.v[i]=1,y=y+Pow;
      if(check(i,x,y)){
        if(!(--n)){
          for(k=i;k;k--)putchar(x.v[k]+'0');
          return 0;
        }
        q1[o^1][++t1[o^1]]=P(x,y);
      }
    }
  }
  return 0;
}
```

**注：** 思路来自 Claris。

---

## 作者：Herobrine6265 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6124)

# 思路

非常好 bfs，使我被紫题吊打

### 为什么是 bfs？
1. 显然如果数字 $k$ 满足题目的要求，那么 $k$ 的后缀一定也满足题目要求；
2. $10^k$ 一定是一个满足条件的数，因为 $10^k=5^k \times 2^k$，所以 $10^k$ 的二进制末尾 $k$ 位一定为 $0$ 且右起第 $k+1$ 位一定是 $1$。

综上所述，我们只需要从已经确定满足题意的数字开始向前面添加 $0/1$ 即可，为了保证数字之间的大小顺序，这里采用 bfs。

不过如果把对同一个数添加 $0$ 和 $1$ 的情况连续的放入搜索队列依然会引起错乱（例如 $00 \rightarrow 000,100$ 时中间的 $001$,$010$,$011$ 三种可能就略过了），解决方法有两种：将添加 $0$ 和 $1$ 的情况分两个队列处理或记录一下操作数，在开始处理加 $0$ 的部分时将加 $1$ 的部分入队，作者在这里采用了第二种方案。

到此为止我们就可以写出一个比较暴力的版本，不过毫无悬念的 TLE 了，因此我们考虑优化。

### 优化

1. 把这个数高精度运算转化为二进制是一个必要步骤，在这块可以考虑专门写一个除 $2$ 的函数来减少运算量；
2. 分析易知若对于满足条件的 $l$ 位数字 $k$ 前想添加 $1\underbrace{000\cdots}_{\text{m 个 0}}$ 后仍然满足题意，则 $k$ 的二进制中右起第 $l+1$ 位到第 $l+1+m+1$ 位均为 $0$，因此可以用一个变量 $cnt$ 来记录当前串前面可以加 $0$ 的数量，其中 $cnt$ 为 $k$ 的二进制串中右起第 $l$ 位前连续的 $0$ 的个数 $-1$，操作时若 $cnt \leqslant 0$ 则不能添加 $0$，若 $cnt<0$ 则不能添加 $1$；当向串前加 $0$ 时 $cnt-1$，加 $1$ 时则重置 $cnt$。

# AC Code
```cpp
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int MAXLEN = 250;

struct BigInt
{
    BigInt(string s = "0") { this->num = s; }

    bool operator!=(BigInt b) { return this->num != b.num; }

    BigInt operator*(BigInt b)
    {
        BigInt a(this->num), ans("");
        if (a.num == "0" || b.num == "0")
            return BigInt("0");
        bool neg = ((a.num[0] == '-') ^ (b.num[0] == '-'));
        if (a.num[0] == '-')
            a.num.erase(0, 1);
        if (b.num[0] == '-')
            b.num.erase(0, 1);
        int len1 = a.num.length(), len2 = b.num.length();
        int c[2 * MAXLEN + 5];
        memset(c, 0, sizeof(c));
        for (int j = 0; j < len2; j++)
        {
            for (int i = 0; i < len1; i++)
            {
                c[i + j] += (a.num[len1 - 1 - i] - '0') * (b.num[len2 - 1 - j] - '0');
                c[i + j + 1] += c[i + j] / 10;
                c[i + j] %= 10;
            }
        }
        for (int i = len1 + len2 + 1; i >= 0; i--)
            ans.num.push_back(c[i] + '0');
        while (ans.num[0] == '0' && ans.num != "0")
            ans.num.erase(0, 1);
        if (neg)
            ans.num = '-' + ans.num;
        return ans;
    }

    string num;
};

BigInt pow2[MAXLEN + 5];
int cnt = 1;

inline BigInt div2(BigInt num)
{
    BigInt ans("");
    int c[MAXLEN + 5];
    memset(c, 0, sizeof(c));
    int len = num.num.length();
    for (int i = 0; i < len; i++)
    {
        if ((num.num[i] - '0') % 2)
            c[i + 1] = 5;
        c[i] += (num.num[i] - '0') / 2;
    }
    if (c[0])
        ans.num = char(c[0] + '0');
    for (int i = 1; i < len; i++)
        ans.num.push_back(char(c[i] + '0'));
    if (ans.num == "")
        ans.num = "0";
    return ans;
}

inline int calc(string dec_str)
{
    int l1 = dec_str.length();
    BigInt dec(dec_str);
    for (int i = 1; i < l1; i++)
        dec = div2(dec);
    if ((dec.num.back() - '0') % 2)
    {
        dec = div2(dec);
        for (int i = 1; true; i++)
        {
            if ((dec.num.back() - '0') % 2)
                return i - 2;
            dec = div2(dec);
        }
    }
    return -114;
}

struct QueueData
{
    string num;
    int cnt;
};

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    queue<QueueData> q, used;
    q.push(QueueData{"0", MAXLEN});
    q.push(QueueData{"1", MAXLEN});
    pow2[cnt] = BigInt("1");
    while (!q.empty())
    {
        QueueData front = q.front();
        q.pop();
        if (cnt == front.num.length())
        {
            cnt++;
            pow2[cnt] = pow2[cnt - 1] * BigInt("2");
            while (!used.empty())
            {
                if (used.front().cnt != -1)
                {
                    QueueData temp = QueueData{'1' + used.front().num, calc('1' + used.front().num)};
                    if (temp.cnt != -114)
                        q.push(temp);
                }
                used.pop();
            }
        }
        if (front.num[0] != '0')
            n--;
        if (!n)
        {
            cout << front.num << endl;
            return 0;
        }
        if (front.cnt > 0)
            q.push(QueueData{'0' + front.num, front.cnt - 1});
        used.push(front);
    }
    return 0;
}
/*
200
1011011011000000

500
11101010111011011000000

1000
11110100000000000000000000000000000000
*/
```

---

## 作者：huangzixi071018 (赞：1)

# 题意：
找到第 $n$ 个数，它的十进制是二进制的后缀。

# 做法：
因为是二进制，所以肯定只用考虑 $0$ 和 $1$。大的满足条件的数一定是由小的满足条件的数前面加一位 $1$ 得到的（因为若 $1$ 加在第 $k$ 位，则十进制加 $10^k$，二进制也要加上，$10^k$ 等于 $5^k$ 乘 $2^k$，所以加的最低位是第 $k$ 位，所以不会对前 $k-1$ 位有影响）。先选择要加 $1$ 的那一位，再取出前面算出的满足条件的数，如果这个数的二进制的第 $k$ 位为 $0$，那么在第 $k$ 为加 $1$ 也满足条件（因为 $5^k$ 模 $2$ 一定为 $1$，所以第 $k$ 位加一之后，二进制上第 $k$ 位肯定也会加一，所以如果二进制上第 $k$ 位为 $1$，就会进位，则第 $k$ 位会变为 $0$，不满足条件）否则不满足条件，可以打上标记（因为如果这一位为 $0$，可二进制中为 $1$，也矛盾，不能成立）。因为加一的 $k$ 位是递增的，所以也不用考虑答案的顺序，找到之后直接输出即可。

# 实现：
取出一个之前满足条件的数，让它除以 $k$ 次 $2$，取出最后一位模 $2$ 的值就是二进制中的第 $k$ 位。再判是否为 $0$ 即可，需要使用高精度。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e4+5;
int len;
struct node{
	vector<int>a;
}d[N];
bool v[N];
void chu2(vector<int>&x){//除以2
	for(int i=x.size()-1;i>=0;i--){
		if(i>0){
			x[i-1]+=(x[i]%2)*10;
		}
		x[i]=x[i]/2;
	}
}
void out(vector<int>x){
	for(int i=x.size()-1;i>=0;i--){
		cout<<x[i];
	}
	cout<<"\n";
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	len=1;
	d[0].a.push_back(0);
	d[1].a.push_back(1);
	for(int k=1;;k++){
		int up=len;
		for(int i=0;i<=up;i++){
			if(v[i])continue;
			vector<int>h;
			h=d[i].a;
			for(int j=1;j<=k;j++){//求二进制中的第k位
				chu2(h);
			}
			if(h[0]%2==0){//第k位是否符合
				h=d[i].a;
				for(int j=d[i].a.size();j<k;j++){//补0
					h.push_back(0);
				}
				h.push_back(1);
				d[++len].a=h;
				if(len>=n){
					out(d[n].a);
					return 0;
				}
			}else{
				v[i]=1;
			}
		}
	}
	return 0;
}
```

---


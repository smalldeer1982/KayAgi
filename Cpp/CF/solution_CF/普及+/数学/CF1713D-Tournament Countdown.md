# Tournament Countdown

## 题目描述

这是一道交互题。

有一场由 $2^n$ 位选手组成的锦标赛。

这个锦标赛的规则如下：第 $1$ 位选手与第 $2$ 位选手竞争，第 $3$ 位选手与第 $4$ 位选手竞争……以此类推，比赛结束时会只剩下一位参赛选手，这位参赛选手就是胜利者。

你不知道比赛的结果，但你想通过询问评审团来得知最后谁赢了。

每次询问评审团，你需要给定两个正整数 $a$ 和 $b$，$a$ 和 $b$ 分别代指两位选手的编号。

若 $a$ 选手 比 $b$ 选手 赢的回合更多，评委团将报出数字 $1$；如果 $b$ 选手 比 $a$ 选手 赢的回合更多，评审团将报出数字 $2$；如果这两位选手赢的回合一样多，评审团会报出数字 $0$。

你要做的是在不超过 $\lceil \frac{1}{3} \cdot 2^{n+1} \rceil$ 的次数内找到最后胜利的选手。此处 $\lceil x \rceil$ 表示四舍五入 $x$ 到最近的整数。

这场锦标赛已经过去很久了。所以保证有唯一解。

## 样例 #1

### 输入

```
1
3

2

0

2```

### 输出

```
? 1 4

? 1 6

? 5 7

! 7```

# 题解

## 作者：Miraik (赞：31)

入门级交互题。

最憨憨的做法就是直接一场一场比赛地询问结果，显然这样做每次询问只能淘汰一个人，总共需要询问 $2^n-1$ 次。

题目中给出的限制即为 $\ \lceil \frac{2}{3}\times 2^n \rceil$，显然在明示我们需要在 $2$ 次询问中淘汰 $3$ 名选手。

很自然的想法就是试着用 $2$ 次询问去比出 $4$ 名选手中的赢家，淘汰剩下 $3$ 名选手。

考虑酱紫的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/6g8csoio.png)

分别记四只小企鹅的胜场数为 $a,b,c,d$。

我们先询问 ![](https://cdn.luogu.com.cn/upload/image_hosting/twr7gcu0.png) 和 ![](https://cdn.luogu.com.cn/upload/image_hosting/54ho61qa.png) 的胜负场关系，即询问 $a$ 和 $d$ 的大小关系。

- 1. $a>d$

首先容易知道：![](https://cdn.luogu.com.cn/upload/image_hosting/twr7gcu0.png) 必然战胜了 ![](https://cdn.luogu.com.cn/upload/image_hosting/r18vdobz.png)，否则 ![](https://cdn.luogu.com.cn/upload/image_hosting/twr7gcu0.png) 止步于至于目前的底层，$a$ 不可能大于 $d$。

此时再询问 $a$ 和 $c$ 的大小关系，分为两种情况：

(1) $a>c$ 说明 ![](https://cdn.luogu.com.cn/upload/image_hosting/twr7gcu0.png) 战胜了 ![](https://cdn.luogu.com.cn/upload/image_hosting/lbzes6lb.png) 和 ![](https://cdn.luogu.com.cn/upload/image_hosting/54ho61qa.png) 中的赢家，因此 ![](https://cdn.luogu.com.cn/upload/image_hosting/twr7gcu0.png) 留下，其它三只企鹅被淘汰。

![](https://cdn.luogu.com.cn/upload/image_hosting/xod46dt6.png)

(2) $a<c$ 说明 ![](https://cdn.luogu.com.cn/upload/image_hosting/twr7gcu0.png) 战胜了 ![](https://cdn.luogu.com.cn/upload/image_hosting/r18vdobz.png)，![](https://cdn.luogu.com.cn/upload/image_hosting/lbzes6lb.png) 战胜了 ![](https://cdn.luogu.com.cn/upload/image_hosting/54ho61qa.png)，然后 ![](https://cdn.luogu.com.cn/upload/image_hosting/lbzes6lb.png) 战胜了 ![](https://cdn.luogu.com.cn/upload/image_hosting/twr7gcu0.png)，因此 ![](https://cdn.luogu.com.cn/upload/image_hosting/lbzes6lb.png) 留下，其它三只企鹅被淘汰。

![](https://cdn.luogu.com.cn/upload/image_hosting/qlnqa29z.png)

容易发现此时不可能出现 $a=c$ 的情况。

- 2. $a<d$

与 (1) 同理，只需要分 $b<d$ 和 $b>d$ 两种情况即可。

- 3. $a=d$

什么时候会出现 $a=d$ 呢？发现此时必然为 ![](https://cdn.luogu.com.cn/upload/image_hosting/twr7gcu0.png) 输给了 ![](https://cdn.luogu.com.cn/upload/image_hosting/r18vdobz.png)，![](https://cdn.luogu.com.cn/upload/image_hosting/54ho61qa.png)输给了 ![](https://cdn.luogu.com.cn/upload/image_hosting/lbzes6lb.png)，因为如果 ![](https://cdn.luogu.com.cn/upload/image_hosting/twr7gcu0.png) 和 ![](https://cdn.luogu.com.cn/upload/image_hosting/lbzes6lb.png) 都先战胜了对手，然后它们碰面，胜场数就必然不等了。

因此只需要分 $b<c$ 和 $b>c$ 两种情况即可。

至此，我们成功在 $2$ 次询问中淘汰掉 $3$ 名选手。

一轮轮不停做即可。剩余最后两名选手时，直接比较即可。时间复杂度 $O(\sum_{i=1}^n 2^i) = O(2^{n+1})$，比较次数 $\lceil \frac{2^{n+1}}{3} \rceil$。

[code](https://codeforces.com/contest/1713/submission/190957473)

---

## 作者：Licykoc (赞：9)

挺有趣的一道题。

突破口在 $ \left \lceil \frac{1}{3} \cdot 2^{n + 1} \right \rceil $ 这个怪异的限制上。

$ \left \lceil \frac{1}{3} \cdot 2^{n + 1} \right \rceil =\lceil \frac{2}{3} \cdot 2^n \rceil$。

这个式子启示我们必须**每两次操作排除三个元素**。还是不会？先来考虑只有 $4$ 个元素 $(a,b,c,d)$ 的情况：

- 第一次先询问 $a,c$。

- 若 $a = c$，显然 $a$ 和 $c$ 都不可能是赢家，转而询问 $b,d$ 即可。

- 若 $a \gt c$，显然 $a$ 可能是赢家且 $c$ 不可能是赢家，同时 $b$ **也不可能是赢家**。因为 $a,b$ 中只可能有一个赢家。所以询问 $a,d$ 即可。

- 若 $a \lt c$，同上，询问 $b,c$ 即可。

上述做法就能在两次操作内排除三个元素，我们只要稍加推广，就能解决此题。这个读者可以自行思考。

代码实现：

```cpp
#include<bits/stdc++.h>
#define UP(x,l,r) for (int x=(int)l;x<=(int)r;++x)
#define DOWN(x,l,r) for (int x=(int)l;x>=(int)r;--x)
#define IOS ios::sync_with_stdio(0),cin.tie(0)
#define low(x) (x&(-x))
#define fi first
#define se second
#define pb push_back
#define isdigit(c) (c>='0'&&c<='9')
using namespace std;
inline void read (int &x) {
    char c=getchar(); int w=0; x=0;
    for (;!isdigit(c);c=getchar()) w^=!(c^45);
    for (;isdigit(c);c=getchar()) x=(x*10)+(c^48);
    x=w?-x:x;
}
typedef pair<int,int> pii;
const int MAXN=2e5+10;
int T,n,m;
int win[MAXN];
signed main () {
    IOS;
    read(T);
    while (T--) {
        read(m); n=(1<<m);
        vector<int> player;
        UP(i,1,n) player.pb(i);
        while (1) {
            vector<int> tmp;
            for (int i=0;i+3<player.size();i+=4) {
                int a,b,c,d,ans;
                a=player[i];
                b=player[i+1];
                c=player[i+2];
                d=player[i+3];
                cout<<"? "<<a<<" "<<c<<endl; cout.flush();
                int x;
                read(x);
                if (!x) {
                    cout<<"? "<<b<<" "<<d<<endl; cout.flush();
                    int y;
                    cin>>y;
                    if (y==1) ans=b; else ans=d;
                }
                if (x==1) {
                    cout<<"? "<<a<<" "<<d<<endl; cout.flush();
                    int y;
                    cin>>y;
                    if (y==1) ans=a; else ans=d;
                }
                if (x==2) {
                    cout<<"? "<<c<<" "<<b<<endl; cout.flush();
                    int y;
                    cin>>y;
                    if (y==1) ans=c; else ans=b;
                }
                tmp.pb(ans);
            }
            if (n!=2) player.swap(tmp);
            if (player.size()==1) break;
            if (player.size()==2) {
                cout<<"? "<<player[0]<<" "<<player[1]<<endl; cout.flush();
                int x; vector<int> tmp;
                cin>>x;
                if (x==1) tmp.pb(player[0]); else tmp.pb(player[1]);
                player.swap(tmp);
                break;
            }
        }
        cout<<"! "<<player[0]<<endl; cout.flush();
    }
}
```

---

## 作者：Monomial (赞：4)

[个人博客体验更佳](https://www.cnblogs.com/shuger/p/16566523.html)

## 题目大意

有 $2^{n}$ 个人进行一轮淘汰赛，每次可以询问其中任意两人谁赢的场数多，最后输出淘汰赛的冠军。

## 分析

一道优质交互题。

首先看最多的交互次数，是 $\lceil \frac{1}{3} \times 2^{n+1} \rceil $ ，即 $\lceil \frac{2}{3} \times 2^{n} \rceil $ ，考虑到总的比赛场数是 $2^{n}-1$ ，可以尝试用 $2$ 次询问获得 $3$ 场比赛的结果。

那么如何用 $2$ 次询问获得 $3$ 场比赛的结果呢？

我们来分析一下，$4$ 个人之间（假设这四个人分别是 $p_{1}$ ， $p_{2}$ ， $p_{3}$ ， $p_{4}$ ），会进行 $3$ 场比赛，先是 $p_{1}$ 和 $p_{2}$ 比赛 ， 然后 $p_{3}$ 和 $p_{4}$ 比赛。我们如果对第一轮直接交战的人进行比较，那么就错了。

我们考虑先对 $p_{1}$ 和 $p_{3}$ 进行比较，如果 $p_{1}$ 和 $p_{3}$ 胜利场数一样，那么他们不可能同时进入下一轮，因为如果同时进入下一轮，他们当中就一定会有一个人胜利，胜利场数就不可能一样，所以直接比较 $p_{2}$ 和 $p_{4}$ 就可以知道这 $4$ 个人中胜者是谁。

接下来分析 $p_{1}$ 比 $p_{3}$ 胜利场数多的情况。在这种情况下，$p_{3}$ 不可能是 $4$ 个人中的胜者，同时 $p_{1}$ 一定通过了第 $1$ 轮，即 $p_{2}$ 不是 $4$ 个人中的胜者了。所以只需要比较 $p_{1}$ 和 $p_{4}$ 即可。

同理，$p_{1}$ 比 $p_{3}$ 胜利场数少时，只需要比较 $p_{2}$ 和 $p_{3}$ 即可。

```cpp
#define sx fflush(stdout)

int win[(1<<17)|5]={};

void wk() {
    int n,result;
    read(n);
    int m=1<<n;
    for(int i=1;i<=m;++i) win[i]=i;
    for(int l=1;l<=n;l+=2,m/=4) {
        if(l==n) {
            printf("? %d %d\n",win[1],win[2]);
            sx;
            read(result);
            if(result==1) {
                printf("! %d\n",win[1]);
            }
            else printf("! %d\n",win[2]);
            sx;
            return ;
        }
        for(int i=1;i*4<=m;++i) {
            printf("? %d %d\n",win[i*4-3],win[i*4-1]);
            sx;
            read(result);
            if(!result) {
                printf("? %d %d\n",win[i*4-2],win[i*4]);
                sx;
                read(result);
                if(result==1) win[i]=win[i*4-2];
                else win[i]=win[i*4];
            }
            else if(result==2) {
                printf("? %d %d\n",win[i*4-2],win[i*4-1]);
                sx;
                read(result);
                if(result==1) win[i]=win[i*4-2];
                else win[i]=win[i*4-1];
            }
            else {
                printf("? %d %d\n",win[i*4-3],win[i*4]);
                sx;
                read(result);
                if(result==1) win[i]=win[i*4-3];
                else win[i]=win[i*4];
            }
        }
    }
    printf("! %d\n",win[1]);
    sx;
}
```

---

## 作者：pvzelyyds (赞：3)

# Solution
这里给出一个每 $4$ 个人询问一次，总询问次数为 $2^{n-1}$ 的做法。

接下来我们以 $n=8$ 的情况举例分析，首先询问 $1\ 3$，如果 $1$ 的胜利次数等于 $3$，那么说明 $1$ 和 $3$ 在该轮同时被淘汰，故 $2$ 和 $4$ 晋级。

接下来考察 $1$ 的胜利次数小于 $3$ 的情况，这种情况下显然 $3$ 必定晋级，但是无法确认 $1 \ 2$ 到底谁晋级，但是我们并不关心这一结果，直接默认 $2$ 晋级即可。理由是假设实际情况是 $1$ 在这一轮晋级，那么由 $3$ 的胜利次数大于 $1$ 可知下一轮 $1$ 必将被 $3$ 淘汰，那么本轮直接假设 $2$ 晋级便不会导致最终答案的错误。

但是在实现的过程中仍需要考虑 $1$ 在本轮晋级对于询问的影响，下面结合具体例子进行分析。$8$ 个人的胜利局数为 $[1,0,3,0,1,0,0,2]$，那么由上述的询问方法询问 $1\ 3$ 以及 $5\ 7$ 之后可知第一局之后 $2,3,5,8$ 四人晋级，但实际情况则是 $1,3,5,8$ 四人晋级，那么下一次再询问 $2\ 5$ 的胜利局数就没有任何的意义，而且也会得出 $5$ 在第二轮晋级的错误结论。由此我们得知在每四个人中，我们应该选择两个**确认晋级**的人进行询问才有意义，比如在上述例子中 在第二轮中应该选择 $3\ 5$ 进行询问而非 $2\ 5$。显然我们总能保证两个人中至少有一个能够**确认晋级**，于是总是能在 $4$ 个人中寻找到 $2$ 个询问对象。在代码实现时只需要将**确认晋级**的人打上 $vis$ 标记即可。

当然接下来考察 $1$ 的胜利次数大于 $3$ 的情况是完全一致的，就不过多赘述了。当最后只剩下 $2$ 个人时，直接询问输出即可。

最后再分析一个例子加深一下理解，$8$ 人的胜利局数为 $[0,3,1,0,2,0,1,0]$。下面粗体标出的即为**确认晋级**的人。

第一轮询问 $1\ 3$ 和 $5\ 7$，得出晋级的人为  $2,$**3**,**5**$,8$，**实际**晋级的人为 $2,3,5,7$。

第二轮询问 $3\ 5$，得出晋级的人为 ***2,5***，**实际**晋级的为 $2\ 5$ (这里 $2$ 变为了确认晋级的人，想一想为什么)。

最后一轮询问 $2\ 5$，得出最终答案为 $2$。

总询问次数为 $2^{n-2}+2^{n-2}+\cdots2^0+1=2^{n-1}$。

时间复杂度 $O(2^n)$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>void outs(const T& h) { cout << h << endl; }
template<typename T, typename...U>void outs(const T& h, const U&...t) { cout << h << " "; outs(t...); }
const int maxn = 1 << 17 | 1;
#define __cs() int T; cin >> T; while (T--)
int n, a[maxn], b[maxn], x, y, z;
bool vis[maxn], tmp[maxn];
void solve() {
    cin >> n;
    for (int i = 1; i <= (1 << n); ++i) {
        vis[i] = 1;
        a[i] = i;
    }
    for (int i = n; i >= 1; --i) {
        if (i == 1) {
            outs("?", a[1], a[2]);
            cin >> x;
            outs("!", x == 1 ? a[1] : a[2]);
        } else {
            int tot = 0;
            for (int j = 1; j <= (1 << i); j += 4) {
                x = (vis[j] ? a[j] : a[j + 1]);
                y = (vis[j + 2] ? a[j + 2] : a[j + 3]);
                outs("?", x, y);
                cin >> z;
                if (z == 0) {
                    b[++tot] = x ^ a[j] ^ a[j + 1];
                    tmp[tot] = 1;
                    b[++tot] = y ^ a[j + 2] ^ a[j + 3];
                    tmp[tot] = 1;
                } else if (z == 1) {
                    b[++tot] = x;
                    tmp[tot] = 1;
                    b[++tot] = y ^ a[j + 2] ^ a[j + 3];
                    tmp[tot] = 0;
                } else {
                    b[++tot] = x ^ a[j] ^ a[j + 1];
                    tmp[tot] = 0;
                    b[++tot] = y;
                    tmp[tot] = 1;
                }
            }
            memcpy(a, b, (tot + 1) * 4);
            memcpy(vis, tmp, tot + 1);
        }
    }
}
int main() {
    __cs()solve();
    return 0;
}
```


---

## 作者：cst_123 (赞：3)

### - [原题传送门](https://codeforces.com/contest/1713/problem/D)

### - [洛谷传送门](https://www.luogu.com.cn/problem/CF1713D)
--------

### 题意

一道交互题。

有多组数据，给你一个数 $n$，表示有 $2^n$ 个人在比赛，一旦有人输了一场就会被淘汰。你需要向评测机询问 $x$ 和 $y$ 谁胜的场次多。

- 若返回 $1$ 表示 $x$ 胜的场次多。
- 若返回 $2$ 表示 $y$ 胜的场次多。
- 若返回 $0$ 表示 $x$ 与 $y$ 胜的场次一样多。

注意询问不得超过 $\frac{1}{3} \times 2^{n+1}$ 次，最终请你输出最后胜出了的人的编号。

### 思路

我们可以将所有人各分成 $4$ 个人一组。

假设 $4$ 个人从小到大分别是 $a$, $b$, $c$, $d$。第一次若询问 $a$ 与 $c$。

- 返回是 $0$，表明 $a$ 与 $c$ 都不是四人中最终获胜的，我们询问 $b$ 和 $d$，因为四人中胜利的人胜的场次是最多的。

- 返回是 $1$，表明 $a$ 必然胜过了 $b$ 也胜过了 $c$，之后询问 $a$ 和 $d$。

- 返回是 $2$，表明 $c$ 胜过了 $a$ 与 $d$，这之后只用询问 $b$ 和 $c$ 了。

四个人不管怎么给的回答，都能用两次找到此次在 $4$ 人中最终获胜的人。

那么此题就可以这么做了，之后，我们在最后时只剩 $1$ 个人或 $2$ 个人时，直接判断并输出。

之后，我们要把每次获胜的人记录下来，这样才能方便继续往下做。

我的做法就是在此多加入一个 $b$ 数组，作用是在询问时，把我们已经知道的获胜的人先存入 $b$ 数组，之后就更新 $n$，现在表示的是现在还有多少个在原先比赛获胜的人，将这个数组中的人反存入原先的 $a$ 数组，这样我们再调亿下细节，此题就结束了。

需要注意的在做这题时，应该根据你的代码询问的具体内容进行询问。如当你的代码在跑样例时询问：

```cpp
? 1 3
```
你就应按照样例给出的图片输入 $1$，也就是 $1$ 胜利的场次比 $3$ 多。

### 代码

```cpp
//交互题需刷新缓冲块，但是使用cin/cout的就按平常做就行了
//若使用scanf/printf的就需加上fflush(stdout)
while(T--){
	cin>>n;
	n=1<<n;//将总人数算出
	for(int i=1;i<=n;i++)//记录每个人的编号
    	a[i]=i;
	while(1){//因为不知道需做多少次，所以先死循环
		if(n==1){//只剩下一人了，输出此人所在的编号
			cout<<"!"<<" "<<a[1]<<endl;
			break;
		}
		if(n==2){//还剩两人，问一下评测机谁胜的场次多，再输出胜者
			cout<<"? "<<a[1]<<" "<<a[2]<<endl;
			cin>>op;
			if(op==1)
				cout<<"! "<<a[1]<<endl;
			else cout<<"! "<<a[2]<<endl;
			break;
		}
		else{
        	//I表示的是现在分成四人组的第一个人是谁
            //num表示有几个人进入了下一轮
			I=1;num=0;
			while(1){//还是不知道要做几轮，于是再来一个死循环
         	  	//x和y表示的是当前比的是谁和谁
				x=I;
				y=I+2;
				if(x>n)//已经超过了n人了，就退出
           			break;
				cout<<"? "<<a[x]<<" "<<a[y]<<endl;
				cin>>op;
				if(op==0){//两人平了，胜者只能是a[x+1]和a[y+1]的人了，便再次询问
					x++;
					y++;
					cout<<"? "<<a[x]<<" "<<a[y]<<endl;
					cin>>op;
					if(op==1){
             			b[num]=a[x];//在b数组存入胜者
                		num++;//人数加1
                		I+=4;//更新，表示下一个四人组的第一个人的编号
                		continue;//完成了，跳过
             		}
					else{b[num]=a[y];num++;I+=4;continue;}
				}
           	    //之后的也就和之前的相差无几了，就不再细讲了
				if(op==1){
					y++;
					cout<<"? "<<a[x]<<" "<<a[y]<<endl;
					cin>>op;
					if(op==1){b[num]=a[x];num++;I+=4;continue;}
					else{b[num]=a[y];num++;I+=4;continue;}
				}
				if(op==2){
					x++;
					cout<<"? "<<a[x]<<" "<<a[y]<<endl;
					cin>>op;
					if(op==1){b[num]=a[x];num++;I+=4;continue;}
					else{b[num]=a[y];num++;I+=4;continue;}
				}
			}
			n=num;//更新还剩下的人的总数
			for(int i=1;i<=n;i++)//把剩下所剩的胜利的人反存入a数组，让a数组继续做上面的判断
				a[i]=b[i];
		}
	}
}
```

---

## 作者：hgzxwzf (赞：3)

交互题真是有意思。

## 思路：

首先很容易想到 $O(2^n)$ 的做法，因为最后的赢家肯定是赢的最多的。

记当前赢的最多的人为 $mx$，比较 $mx$ 和当前枚举的人，如果返回 $2$，将 $mx$置为当前的这个人，否则不变。

这样做显然要查询 $2^n-1$ 次，但题目要求不超过 $\lceil\frac{1}{3}\cdot2^{n+1}\rceil$ 次，大约 $\lceil\frac{2}{3}\cdot2^n\rceil$ 次，无法通过。

先考虑每个人的第一场。

比如选手 $1,2,3,4$，我们先比较 $1$ 和 $3$，分三种情况：

- $0$：说明 $1$ 输给了 $2$，$3$ 输给了 $4$。

因为如果 $1$ 或 $3$ 其中一个人在第一场比赛中赢了，那么在一场中输的那个人至少比另一个人少赢一局；如果 $1$ 和 $3$ 都赢了，那么 $1$ 和 $3$ 其中一个人就会在第二场比赛中输给对方，那么对方就会比自己至少多赢一局。

然后我们比较 $2$ 和 $4$，胜场多的人进入第三场比赛。

- $1$：说明 $2$ 输给了 $1$，$3$ 肯定不能进入第三场比赛。

$1$ 胜场至少为 $1$，所以他要赢 $2$。$3$ 的胜场 没有 $1$ 多，如果他都能进第三场比赛，那么 $1$ 肯定也能进，这是不被允许的。

然后我们比较 $1$ 和 $4$，胜场多的人进入第三场比赛。

- $2$：同 $1$。

这样通过 $\frac{1}{2}\cdot2^n$ 次查询选手就从 $2^n$ 变为了 $2^{n-2}$。

显然可以递归或者迭代处理。

时间复杂度：emm...本蒟蒻不太会证明，但是可以 AC 这道题。

## Code:
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<stack>
#include<cmath>
#include<vector>
#include<iostream>

#define per(x,y,z) for(int x=z;x>=y;x--)
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define LL long long
#define int_ __int128

using namespace std;
const int N=1<<17;

int win[N],twin[N];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		int tot=(1<<n);
		rep(i,1,tot) win[i]=i;
		while(1)
		{
			if(tot==1)
			{
				cout<<'!'<<' '<<win[1]<<endl;
				break;
			}
			if(tot==2)
			{
				int res;
				cout<<'?'<<' '<<win[1]<<' '<<win[2]<<endl;
				cin>>res;
				if(res==1) cout<<'!'<<' '<<win[1]<<endl;
				else cout<<'!'<<' '<<win[2]<<endl;
				break;
			}
			int ttot=0;
			for(int i=1;i+3<=tot;i+=4)
			{
				int res;
				cout<<'?'<<' '<<win[i]<<' '<<win[i+2]<<endl;
				cin>>res;
				if(res==0)
				{
					cout<<'?'<<' '<<win[i+1]<<' '<<win[i+3]<<endl;
					cin>>res;
					if(res==1) twin[++ttot]=win[i+1];
					else twin[++ttot]=win[i+3];
				}
				else if(res==1)
				{
					cout<<'?'<<' '<<win[i]<<' '<<win[i+3]<<endl;
					cin>>res;
					if(res==1) twin[++ttot]=win[i];
					else twin[++ttot]=win[i+3];
				}
				else
				{
					cout<<'?'<<' '<<win[i+1]<<' '<<win[i+2]<<endl;
					cin>>res;
					if(res==1) twin[++ttot]=win[i+1];
					else twin[++ttot]=win[i+2];
				}
			}
			rep(i,1,ttot) win[i]=twin[i];
			tot=ttot;
		}
	}
	return 0;
}
  ```

---

## 作者：LHQing (赞：2)

### 题目分析：

我们先看题目的已知：给定已知的人数，和部分已知比赛。这里已知的比赛是指最顶层的比赛，比如样例中 $1$ 和 $2$ 比赛，$3$ 和 $4$ 比赛 是已知的。

既然相互谁和谁比赛已知，那么四个同层次的选手比赛，我们逐出四个人中的王者。比如 $1,2,3,4$ 比赛，第一轮刷下了 $2,3$，那么 $2$ 和 $3$ 就排名一样，我们再对 $1,4$ 考虑就行。这样 $2$ 次询问筛掉 $3$ 人。

具体流程如下：我们每次选出四个相同层次比赛的人，我们让第 $1$ 位和第 $3$ 位相比较，如果返回 $1$，那么让 $1$ 和 $4$ 相比较；若返回 $2$，那么 让 $2$ 和 $3$ 相比较；若返回 $0$，那么让 $2$ 和 $4$ 比较。最后选出那个四个人中的王者。

因为 $\lceil\frac{1}{3}\times2^{n+1}\rceil=\lceil\frac{2}{3}\times2^n\rceil$，而我们询问是用 $2$ 次淘汰 $3$ 人，能够通过本题。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pd push_back
#define all(x) x.begin(),x.end()
#define Clear(x,n) for(int i=0;i<=n;i++)x[i]=0;
//==============================================================================
ll QP(ll x,ll y,ll mod){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}
//==============================================================================
namespace IO{
	int readInt(){
		int x=0,y=0;char c=0;
		while(!isdigit(c))y|=c=='-',c=getchar();
		while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return !y?x:-x;
	}
	void write(int x){if(!x)return;write(x/10);putchar(x%10);}
	void Output(int x){if(x<0)putchar('-'),x=-x;if(!x)putchar('0');else write(x);}
	void WL(int x){Output(x);putchar('\n');}
	void WS(int x){Output(x);putchar(' ');}
}
namespace Debug{
	void DeVec(vector<int> c){for(auto y:c)printf("%d ",y);puts("");}
	void DeNum(int x){printf("%d\n",x);}
}
//==============================================================================
const int N=1e5+10;
vector<int> a;
int T;
int ask(int x,int y){cout<<"? "<<x<<' '<<y<<'\n';fflush(stdout);cin>>x;return x;}
void query(int x){cout<<"! "<<x<<'\n';fflush(stdout);}
int Gval(vector<int> v){
	int p=ask(v[0],v[2]);
	if(p==1){
		p=ask(v[0],v[3]);
		return p==1?v[0]:v[3];
	}if(p==2){
		p=ask(v[1],v[2]);
		return p==2?v[2]:v[1];
	}if(p==0){
		p=ask(v[1],v[3]);
		return p==1?v[1]:v[3];
	}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    cin>>T;
    while(T--){
    	a.clear();int n;cin>>n;
    	for(int i=1;i<=(1<<n);i++)a.pd(i);
    	while(a.size()>2){
    		vector<int> b;
    		#define End(x) x.pd(a.back()),a.pop_back()
    		while(!a.empty()){
    			vector<int> v;
    			for(int i=1;i<=4;i++)End(v);
    			b.pd(Gval(v));
			}a=b;
		}if(a.size()==2){
			int p=ask(a[0],a[1]);
			if(p==2)a[0]=a[1];
		}query(a[0]);
	}return 0;
}
/*
16

8+2
*/

```

---

## 作者：cachejtt (赞：1)

## 题意
**这是一道交互题。**

有 $2^n$ 个人比赛，每轮实行两人一组，一组仅胜出一人进入下一轮。你需要得出最终胜者。

每次询问，你输出 `? l r`，代表询问编号为 $l$ 的人和编号为 $r$ 的人。

系统会返回一个结果 $res$。若 $res=1$，代表 $l$ 的胜场多于 $r$；若 $res=2$，代表 $r$ 的胜场多于 $l$；若 $res=0$，代表两者胜场一样多。最后以 `! p` 的形式输出胜者编号 $p$。

要求询问次数不超过 $\lceil \dfrac{2}{3} \times 2^n \rceil$。

## 思路
### 朴素想法
每次询问当前小组的胜者，并处理完当前这一轮，再处理下一轮，最终得到胜者。

例如对于 $n=2$ 的情况：

1. 询问 $1,2$，得到 $1,2$ 中的胜者 $w_l$；
2. 询问 $3,4$，得到 $3,4$ 中的胜者 $w_r$；
3. 询问 $w_l,w_r$，得到最终胜者 $w_p$；

因此对于这种朴素方案，询问次数是 $2^{n-1}+2^{n-2}+\dots+1=2^n-1$ 的，显然不够优秀。

### 考虑优化次数
我们不妨称类似于从 $1,2,3,4$ 中选出最终胜者的操作为四进一，考虑如何优化。

之前的朴素算法，我们需要询问三次才能得出最终胜者，所以如果对于每一个四进一，如果我们只需要两次询问就能得到最终胜者的话，次数就控制在了原来的 $\dfrac{2}{3}$，即可通过。

那么，如何通过两次询问找到四个人中的胜者呢？

考虑四个人的胜场数。这里我们仅考虑这四个人四进一的胜场，不考虑胜者继续向上赢的胜场数。那么四个人的胜场数，一定是 $0,0,1,2$。也就是说，其中有两个人赢了 $0$ 场，一个人赢了 $1$ 场，一个人赢了 $2$ 场。

那么有如下八种情况。
![四进一](https://cdn.luogu.com.cn/upload/image_hosting/2dbpcvot.png)

我们记 $[x,y]\to res$ 为询问 `? x y`，返回值为 $res$。

此时我们先 $[1,3]\to res_1$。

1. 当 $res_1=1$，情况有第 $1,3,4$ 种，因此接下来应 $ [1,4]\to res_2$，若 $res_2=1$，情况有第 $1,3$ 种，但胜者均为 $1$ 号；若 $res_2=2$，情况仅有第 $4$ 种，胜者为 $4$ 号。
2. 当  $res_1=2$，情况有第 $2,5,6$ 种，因此接下来应 $[2,3]\to res_2$，若 $res_2=1$，情况仅有第 $5$ 种，胜者为 $2$ 号；若 $res_2=2$，情况有第 $2,6$ 种，但胜者均为 $3$ 号。
3. 当 $res_1=0$，情况有第 $7,8$ 种，因此接下来应 $[2,4]\to res_2$，如果 $res_2=1$，情况为第 $7$ 种，胜者为 $2$ 号；如果 $res_2=2$，情况为第 $8$ 种，胜者为 $4$ 号。

这样，我们仅用两次询问，就实现了四进一。

在向下递归时，把当前长度分成四份，分别去做结果，再上传即可。

在代码实现时注意细节。注意特判 $n=1$ 的情况，并且当 $n$ 为奇数时，要先分成两部分，再各自去做，最后一次询问两个部分的返回结果就可以。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
int t,n,res;
int q(int l1,int l2,int r1,int r2){
  cout<<"? "<<l1<<" "<<r1<<endl;
  cin>>res;
  if(res==1){
    cout<<"? "<<l1<<" "<<r2<<endl;
    cin>>res;
    if(res==1)return l1;
    if(res==2)return r2;
  }
  else if(res==0){
    cout<<"? "<<l2<<" "<<r2<<endl;
    cin>>res;
    if(res==1)return l2;
    if(res==2)return r2;
  }
  else if(res==2){
    cout<<"? "<<l2<<" "<<r1<<endl;
    cin>>res;
    if(res==1)return l2;
    if(res==2)return r1;
  }
  return 0;
}
int solve(int s,int t){
  int l1,l2,r1,r2,res;
  int r=t,l=s;
  if(r-l==1){
    cout<<"? "<<l<<" "<<r<<endl;
    cin>>res;
    if(res==1)return l;
    if(res==2)return r;
  }
  if(r-l==3){
    cout<<"? "<<l<<" "<<l+2<<endl;
    cin>>res;
    if(res==1){
      cout<<"? "<<l<<" "<<r<<endl;
      cin>>res;
      if(res==1)return l;
      if(res==2)return r;
    }
    else if(res==0){
      cout<<"? "<<l+1<<" "<<r<<endl;
      cin>>res;
      if(res==1)return l+1;
      if(res==2)return r;
    }
    else if(res==2){
      cout<<"? "<<l+1<<" "<<l+2<<endl;
      cin>>res;
      if(res==1)return l+1;
      if(res==2)return l+2;
    }
  }
  if(n%2==1){
    n--;
    l1=solve(s,(s+t-1)>>1);
    l2=solve(((s+t-1)>>1)+1,t);
    cout<<"? "<<l1<<" "<<l2<<endl;
    cin>>res;
    if(res==1)return l1;
    if(res==2)return l2;
  }
  l1=solve(s,s+(t-s+1)/4-1);
  l2=solve(s+(t-s+1)/4,(s+t-1)/2);
  r1=solve((s+t-1)/2+1,t-(t-s+1)/4);
  r2=solve(t-(t-s+1)/4+1,t);
  return q(l1,l2,r1,r2);
}
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  int ans;
  rep(kk,1,t){
    cin>>n;
    if(n==1){
      cout<<"? 1 2"<<endl;
      cin>>res;
      if(res==1)cout<<"! 1"<<endl;
      if(res==2)cout<<"! 2"<<endl;
      continue;
    }
    ans=solve(1,(1<<n));
    cout<<"! "<<ans<<endl;
  }
  return 0;
}
```

---

## 作者：Ender_hz (赞：1)

# 题意

*这是一道交互题。*

在一场比赛中有 $2^n$ 位参赛者，第一轮比赛中 $1$ 号选手与 $2$ 号选手对抗，$3$ 号选手与 $4$ 号选手对抗，以此类推，胜者进入下一轮；第二轮比赛中 $1,2$ 中的胜者与 $3,4$ 中的胜者进行对抗，最终只有一个胜者。你可以对两位选手 $a,b$ 进行询问，系统将会返回：

+ $1$，如果 $a$ 赢的场数比 $b$ 多；
+ $2$，如果 $a$ 赢的场数比 $b$ 少；
+ $0$，如果 $a,b$ 赢的场数相等。

你需要在 $\left\lceil\dfrac13\cdot2^{n+1}\right\rceil$ 次询问内找到最终的胜者。

# 分析

> 「他的要求就是2/3 * 2^n 所以其实很能启示复杂度」
>
> —— @ [尹吴潇](https://www.luogu.com.cn/user/21177)

下用 $[a,b]\rightarrow c$ 简记一次对 $a,b$ 的询问，胜场较多的记为 $c$，若胜场相同则 $c=0$。

当每次询问淘汰人数的数学期望为 $k$ 时，询问次数为 $\left\lceil\dfrac{2^n-1}k\right\rceil$，由于题目要求的询问次数 $\le\left\lceil\dfrac23\cdot2^n\right\rceil$，故 $k\ge\dfrac32$

不难想到最朴素的算法：第一次询问 $[1,2] \rightarrow c_1$，第二次询问 $[c_1,3] \rightarrow c_2$，以此类推，最终胜者为 $c_{2^n-1}$；这种算法中 $k=1$，询问次数为 $2^n-1$ ，显然超限。

观察到整棵树由 $2^n-1$ 个 $2$ 进 $1$ 的分形构成，由此想到分治：对于每个 $2$ 进 $1$ 的分形，进行 $1$ 次询问得到胜者，如 $1,2,3,4$ 号选手，在树中为 $3$ 个 $2$ 进 $1$ 的分形，通过 $3$ 次询问：$[1,2] \rightarrow c_1, [3,4] \rightarrow c_2,[c_1,c_2] \rightarrow c_3$ 可以得出胜者 $c_3$，但此算法中 $k$ 的值较上算法不变，询问次数也不变，没有起到实质性的优化效果。

此时想到，若能在 $4$ 进 $1$ 的分形中通过 $2$ 次询问处理出胜者，就能使 $k=\dfrac32$，满足复杂度要求。

下用三元数组 $[w_l,w_r,w_f]$ 分别代表 $4$ 进 $1$ 分形中 $3$ 场 $2$ 进 $1$ 的胜者，其中 $w_l\in\{1,2\}, w_r\in\{3,4\}, w_f\in\{1,2,3,4\}$。

枚举得出，$4$ 进 $1$ 的不同情况共有 $8$ 种，分别为：$①[1,3,1], ②[1,3,3], ③[1,4,1], ④[1,4,4], ⑤[2,3,2], ⑥[2,3,3], ⑦[2,4,2], ⑧[2,4,4]$。

接下来考虑如何在 $2$ 次询问内确定 $w_f$：

+ 初始状态下，$1$ 与 $2$ 等价，$3$ 与 $4$ 等价，若第一次询问 $[1,2]\rightarrow w_l$，则与先前的方法无异，故第一次询问应为 $[1,3]\ \text{or}\ [1,4]\rightarrow w'$，下面的思路中采取 $[1,3]\rightarrow w’$；
+ 对 $w'$ 进行讨论：
    + $w’=1$ 时，对应的情况有 $①[1,3,1], ③[1,4,1], ④[1,4,4]$，此时 $w_f\in\{1,4\}$，因此第二次询问 $[1,4]\rightarrow w_f$ 即可；
    + $w'=3$ 时，对应的情况有 $②[1,3,3], ⑤[2,3,2], ⑥[2,3,3]$，此时 $w_f\in\{2,3\}$，因此第二次询问 $[2,3]\rightarrow w_f$ 即可；
    + $w’=0$ 时，对应发情况有 $⑦[2,4,2], ⑧[2,4,4]$，此时 $w_f\in\{2,4\}$，因此第二次询问 $[2,4]\rightarrow w_f$ 即可。

这样，我们已经构造出了 $k = \dfrac32$ 的算法，剩下的只有一些细节了，例如当 $n$ 为奇数时，最后一次是 $2$ 进 $1$ 而非 $4$ 进 $1$，可以先对左右半棵树分别处理，最后通过一次询问得出最终胜者。

# 代码

```cpp
#include<iostream>
#define il inline
using namespace std;
int T, N;
il int query(int x, int y) {
    int res;
    cout << "? " << x << " " << y << endl;
    cin >> res;
    return res;
}
il int solve(int l, int p) {//(l, l + 2^p]
    if(!p)
        return l + 1;
    int n1, n2, n3, n4, res;
    p -= 2;
    n1 = solve(l, p);
    n2 = solve(l + (1 << p), p);
    n3 = solve(l + (2 << p), p);
    n4 = solve(l + (3 << p), p);
    res = query(n1, n3);
    if(res == 1) {
        res = query(n1, n4);
        if(res == 1)
            return n1;
        else
            return n4;
    }
    if(res == 2) {
        res = query(n2, n3);
        if(res == 1)
            return n2;
        else
            return n3;
    }
    if(res == 0) {
        res = query(n2, n4);
        if(res == 1)
            return n2;
        else
            return n4;
    }
    return 0;
}
signed main(void) {
    ios::sync_with_stdio(false);
    cin >> T;
    int res;
    while(T--) {
        cin >> N;
        if(N & 1) {
            --N;
            int l = solve(0, N), r = solve((1 << N), N);
            res = query(l, r);
            cout << "! " << (res == 1 ? l : r) << endl;
            continue;
        }
        res = solve(0, N);
        cout << "! " << res << endl;
    }
    return 0;
}
```

---

## 作者：wlmqlzm (赞：0)

## CF1713D Tournament Countdown
#### 题意简述：
首先，这是一道有趣交互题。给定 $n$ ，有 $2^n$ 个人进行淘汰赛，图中 $n=3$ 。
![](https://espresso.codeforces.com/398ffa6c381e06b463f3ef9ce10b43e9e016b24c.png)  
你可以询问 $\lceil \frac{1}{3} \cdot 2^{n+1}\rceil$ 次，在询问次数内要给出最终答案：冠军的编号。   
每次询问输出两个要询问的对象的编号 $a$ 和 $b$ 。如果 $a$ 比 $b$ 赢的场次多，返回 $1$ ；如果 $a$ 比 $b$ 赢的场次少，返回 $2$ ；如果 $a$ 和 $b$ 赢的场次一样，返回 $0$ 。  
关于交互题的格式和具体细节，请阅读[原题](https://codeforces.com/contest/1713/problem/D)，这里不做解释。
***
最先考虑的，应该是询问次数。如果读者无法通过上述式子推出询问次数，可以将值带进去。  
容易发现，对于每四个人，只能询问**两次**。而且不难看出，这道题是**递归**询问。
***
接下来该考虑如何询问两次得到答案。注意，询问结果是关于**赢的场次**。
所以，我们可以将 $4$ 个人中赢的场次的可能列出来。  
这里列出最小范围 $4$ 个人的可能场次，分别是： $2,1,0,0$ 。为了方便，记这 $4$ 个人分别为 $a,b,c,d$ ，且 $a$ 赢的场次为 $f(a)$ ，并且第一场 $a$ 对 $b$ ， $c$ 对 $d$ 。  
这样，我们就可以询问 $a$ 和 $c$ 。 
- 返回 $1$ 。则 $f(a)>f(c)$ ，那么 $f(a)=1$ 或 $2$ ，所以 $a$ 一定是赢了 $b$ ，这时只需要询问 $a$ 和 $d$ ，以确定谁赢了 $2$ 场。
- 返回 $2$ 。则 $f(a)<f(c)$ ，那么 $f(c)=1$ 或 $2$ ，同理，只需询问 $b$ 和 $c$ 。
- 返回 $0$ 。则 $f(a)=f(c)=0$ ，只需询问 $b$ 和 $d$ 。  

然后再在每 $4$ 个赢了 $2$ 场的人进行相同的操作。
***
虽然这道题是递归思想，但慎用递归实现，如果写不好很容易就挂了，笔者是使用两个队列模拟的，较麻烦。读者自行尝试两种写法。
### code：
~~~ cpp
while(T--)
{
	lans=0;
	cin>>n;
	t=pow(2,n);\\总人数
	for(i=1;i<=t;i++)
	a[i]=i;
	while(t>1)
	{
		tmp=0;\\每轮将4个人中的胜者存到b里，每轮结束后再赋回a
		if(t!=2)\\有可能最终只剩两个人
		{
			for(i=1;i<=t;i+=4)
			{
				int x,y,z,k;
				x=a[i],y=a[i+1],z=a[i+2],k=a[i+3];
				ans=ask(x,z);\\ask函数是询问
				if(ans==1)
				{
					ans=ask(x,k);
					if(ans==1) b[++tmp]=x;
					else b[++tmp]=k;
				}
				else if(ans==2)
				{
					ans=ask(z,y);
					if(ans==1) b[++tmp]=z;
					else b[++tmp]=y;
				}
				else
				{
					ans=ask(y,k);
					if(ans==1) b[++tmp]=y;
					else b[++tmp]=k;
				}
			}
			t/=4;
		}
		else
		{
			ans=ask(a[1],a[2]);
			if(ans==1) lans=a[1];
			else lans=a[2];
			t/=2;
			break;
		}
		for(i=1;i<=tmp;i++)
		a[i]=b[i];
}
~~~


---

## 作者：lsj2009 (赞：0)

## Problem

交互题，详见题面。

link-><https://codeforces.com/contest/1713/problem/D>。

## Solution

我们考虑四个四个进行分组：维护一个队列，每次取出前 $4$ 个，$a,b,c,d$，其中 $a$ 和 $b$ 的胜者与 $b$ 和 $d$ 的胜者再对决，我们需要求出 $a,b,c,d$ 的最终胜者，先询问 $a,d$，如果相等，则胜者必在 $b,c$ 中，再询问一次即可；如果 $a$ 胜了 $d$（直接或 $d$ 已经输给了 $c$），则将 $a$ 与 $c$ 比较；反之亦然。这样每次询问减少 $3$ 个人，询问 $2$ 次，复杂度 $\frac{2\times2^n}{3}$。

## Code
```cpp
#include<bits/stdc++.h>
#define F fisrt
#define S second
#define INF 0x7fffffff
#define inf 0x3f3f3f3f
#define inf 0x3f3f3f3f3f3f3f3f
//#define int long long
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;

signed main() {
	int T;
	cin>>T;
	while(T--) {
		int n;
		cin>>n;
		queue<int> que;
		_for(i,1,(1<<n))
			que.push(i);
		while(que.size()>=4) {
			int a=que.front(); que.pop();
			int b=que.front(); que.pop();
			int c=que.front(); que.pop();
			int d=que.front(); que.pop();
			int val;
			cout<<"? "<<a<<" "<<d<<endl;
			cin>>val;
			if(val==0) {
				cout<<"? "<<b<<" "<<c<<endl;
				cin>>val;
				if(val==1)
					que.push(b);
				else
					que.push(c);
			} else if(val==1) {
				cout<<"? "<<a<<" "<<c<<endl;
				cin>>val;
				if(val==1)
					que.push(a);
				else
					que.push(c);
			} else {
				cout<<"? "<<b<<" "<<d<<endl;
				cin>>val;
				if(val==1)
					que.push(b);
				else
					que.push(d);
			}
		}
		if(que.size()!=1) {
			int a=que.front(); que.pop();
			int b=que.front(); que.pop();
			cout<<"? "<<a<<" "<<b<<endl;
			int val;
			cin>>val;
			if(val==1)
				que.push(a);
			else
				que.push(b);
		}
		cout<<"! "<<que.front()<<endl;
	}
	return 0;
}
```

---

## 作者：RabbieWjy (赞：0)

## 题意

这是一道交互题。

有一场 $2^n$ 个人参加的淘汰赛，结果已定，你最多使用 $ \left \lceil \frac{1}{3} \cdot 2^{n + 1} \right \rceil $ 次询问，求出淘汰赛的冠军编号。每次询问的格式为 `? a b`，表示询问编号为 $a$ 的人和编号为 $b$ 的人哪个赢的次数多，询问的答案为 $0$ 或 $1$ 或 $2$ 表示 $a$ 赢的场数等于、大于或小于 $b$。最后输出 `! a`，表示淘汰赛的冠军编号。

$1 \leq n\leq 17$。



## 思路

先考虑 $n=1$ 的情况，显然直接询问 `? 1 2` 即可求出答案。



考虑 $n=2$ 的情况，

[![vlK3X8.png](https://s1.ax1x.com/2022/08/09/vlK3X8.png)](https://imgtu.com/i/vlK3X8)

如图，$1$ 和 $2$ 中一定有一个在第一轮就被淘汰了，$3$ 和 $4$ 也是，第一轮之后剩下的两个一定有一个是冠军，赢的场数一定不同且比被淘汰的人多。被淘汰的人赢的场数是一样的。

我们可以询问 `? 1 3`，如果得到答案是 $0$，就得出 $1$ 和 $3$ 都被淘汰了，冠军只可能是 $2$ 或 $4$，一次询问得出答案；

如果答案是 $1$ 或 $2$，那么赢的场数较少的那一个人一定不可能是冠军，和赢的场数较多的人在第一轮比赛的人也一定不可能是冠军。因此就只剩两个人有可能是冠军了，一次询问得出答案。

综上，$n=2$ 时，可以通过两次询问确定答案。



考虑 $n > 2$ 的情况。



当 $2 \mid n$ 时，画出来的赛况图（像样例解释那样的）一定可以分为若干个 $n=2$ 的情况。考虑对赛况图进行搜索，用每个点代表**这一层代表的轮**中**这一个位置人的编号**，则根节点的值就是答案，如样例中的图：

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1713D/27b478ab2bf58dd616a7ef478d5125bdbaa0416b.png)

对于每个从上往下数奇数层（除最后一层外）上的点，一定可以从最后一层开始用 $2$ 次询问求出这个点的答案，再用这个答案往上求答案。此时总共有 $2^n (\frac {1}{2}+\frac{1}{8}+\frac{1}{32}+\dots+\frac{1}{2^{n-1}}) = 2^{n-1}(1+\frac{1}{4}+\frac{1}{16}+\dots+\frac{1}{2^{n-2}})=2^{n-1}\times \frac{4}{3}(1-\frac{1}{2^n})=\frac{1}{3}\times 2^{n+1}(1-\frac{1}{2^n})$ 次询问，满足题意；



当 $2 \nmid n$ 时，画出来的赛况图一定可以分为若干个 $n=2$ 的情况和一个 $n=1$ 的情况，可以类比 $2 \mid n$ 的情况。此时总共有 $2 ^n (\frac{1}{2}+\frac{1}{8}+\frac{1}{32}+\dots+\frac{1}{2^{n-2}})+1 = 2^n(\frac{1}{2}+\frac{1}{8}+\frac{1}{32}+\dots+\frac{1}{2^{n-2}}+\frac{1}{2^n}) = 2^{n+1}\times \frac{4}{3}(1 - \frac{1}{2^{n+1}})$ 次询问，满足题意。



## 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int t,n,m;
int ans[600010];

void dfs(int x,int l,int r,int dep)
{
	if (l == r)
	{
		ans[x] = l;
		return ;
	}
	dfs(x << 1,l,(l + r) / 2,dep + 1);
	dfs(x << 1 | 1,(l + r) / 2 + 1,r,dep + 1);
	if (dep % 2 == 1 - n % 2)
	{
		int res = 0;
		printf("? %d %d\n",ans[x << 2],ans[(x << 1 | 1) << 1]);
		fflush(stdout);
		scanf("%d",&res);
		if (res == 2)
		{
			printf("? %d %d\n",ans[x << 2 | 1],ans[(x << 1 | 1) << 1]);
			fflush(stdout);
			scanf("%d",&res);
			if (res == 2) ans[x] = ans[(x << 1 | 1) << 1];
			else ans[x] = ans[x << 2 | 1];
		}
		else if (res == 1)
		{
			printf("? %d %d\n",ans[x << 2],ans[(x << 1 | 1) << 1 | 1]);
			fflush(stdout);
			scanf("%d",&res);
			if (res == 2) ans[x] = ans[(x << 1 | 1) << 1 | 1];
			else ans[x] = ans[x << 2];
		}
		else
		{
			printf("? %d %d\n",ans[x << 2 | 1],ans[(x << 1 | 1) << 1 | 1]);
			fflush(stdout);
			scanf("%d",&res);
			if (res == 2) ans[x] = ans[(x << 1 | 1) << 1 | 1];
			else ans[x] = ans[x << 2 | 1];
		}
		return ;
	}
}

int main()
{
	scanf("%d",&t);
	while (t --)
	{
		scanf("%d",&n);
		m = (1 << n);
		for (int i = 1;i <= m;i ++) ans[(1 << n - 1) + i] = i;
		dfs(1,1,m,1);
		if (n % 2 == 1)
		{
			int res;
			printf("? %d %d\n",ans[2],ans[3]);
			fflush(stdout);
			scanf("%d",&res);
			if (res == 2) ans[1] = ans[3];
			else ans[1] = ans[2];
		}
		printf("! %d\n",ans[1]);
		fflush(stdout);
	}
}
```



---


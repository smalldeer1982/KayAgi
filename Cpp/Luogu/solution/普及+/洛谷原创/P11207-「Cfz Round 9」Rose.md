# 「Cfz Round 9」Rose

## 题目描述

你和她正在进行一个游戏。

你和她各有 $n$ 张**有序的**卡牌，每张卡牌的颜色可能为粉色、紫色或白色。

**从她开始**，你和她需要各自按照卡牌的顺序，轮流打出手里的卡牌。打出的卡牌将会被移至牌堆中。

若某个人打出卡牌后，牌堆中三种颜色的卡牌的数量相同，则这个人获胜，游戏结束。若你和她的卡牌都打完后，还没有人获胜，则游戏平局。

在游戏开始前，你可以进行若干次操作。每次操作，你可以给任意一个人的任意一张卡牌更换颜色。

你想求出，你至少需要进行多少次操作才能**使她获胜**。可以证明，一定存在至少一种可以使她获胜的操作方案。

## 说明/提示

#### 「样例解释 #1」

对于第 $1$ 组测试数据，不需要进行操作就能使她获胜。

对于第 $2$ 组测试数据，一种可能的操作方案为将她的第 $4$ 张卡牌和第 $5$ 张卡牌的颜色均更换为紫色。

对于第 $3$ 组测试数据，一种可能的操作方案为将你的第 $4$ 张卡牌的颜色更换为白色。

#### 「数据范围」

对于所有测试数据，保证：

- $1 \le T \le 30$；
- $2 \le n \le 10^5$；
- 对于所有不大于 $n$ 的正整数 $i$，满足 $s_i$ 和 $t_i$ 均为 `PVW` 中的某个字符。

**本题采用捆绑测试。**

- Subtask 0（18 points）：$n \le 6$。
- Subtask 1（20 points）：$n \le 1000$。
- Subtask 2（12 points）：对于任意不大于 $n$ 的正整数 $i$，都满足 $s_i \ne t_i$。
- Subtask 3（25 points）：若你不进行任何操作，则你不会获胜。
- Subtask 4（25 points）：无特殊限制。

## 样例 #1

### 输入

```
3
2
PW
VP
5
PPWWP
PWVWV
6
WVPPWW
VVPVWP```

### 输出

```
0
2
1```

# 题解

## 作者：Petit_Souris (赞：6)

把两个序列轮流拼接成 $s_1t_1s_2t_2\dots s_nt_n$，她的回合对应一个奇前缀，你的回合对应一个偶前缀。

容易发现答案不超过 $2$：只需要修改你的第一张牌和她的第二张牌就一定可以让她获胜。

所以只需要判断答案是否为 $0$ 或 $1$，剩下的情况都是 $2$。

答案为 $0$ 直接扫一遍就行了。

答案为 $1$ 可以考虑枚举她获胜的是哪一轮，需要满足这一位上三种颜色的出现次数恰好为 $x-1,x,x+1$（否则无法一次调整得到），这时候会把 $x+1$ 对应的颜色修改一个给 $x-1$。

但是我们还要限制你不能在她之前获胜。设修改的位置为 $p$，她获胜的前缀是 $[1,i]$，那么 $[p,i-1]$ 中不能存在你的一个前缀的出现次数也形如 $y-1,y,y+1$ 且对应颜色相等（因为改完之后你就先获胜了），且 $[1,p-1]$ 中不能存在一个你的前缀使得你会获胜。

容易发现限制的 $p$ 是一段区间，可以维护出来，用前缀和判断是否存在合法的 $p$ 即可，时间复杂度 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=1e6+9;
ll T,n,a[N],sm[N][3];
char s[N],t[N],st[N];
void solve(){
    n=read();
    scanf("%s%s",s+1,t+1);
    rep(i,1,n)st[i*2-1]=s[i];
    rep(i,1,n)st[i*2]=t[i];
    rep(i,1,n*2){
        if(st[i]=='P')a[i]=0;
        else if(st[i]=='V')a[i]=1;
        else a[i]=2;
    }
    rep(i,1,n*2){
        rep(j,0,2)sm[i][j]=sm[i-1][j]+(a[i]==j);
    }
    ll fl=-1;
    rep(i,1,n*2){
        if(sm[i][0]==sm[i][1]&&sm[i][0]==sm[i][2]){
            fl=i;
            break;
        }
    }
    if(fl!=-1&&(fl&1))return puts("0"),void();
    if(fl==-1)fl=n*2;
    map<vector<ll>,ll>mp;
    ll pos[3]={0,0,0};
    rep(i,1,n*2){
        ll b[3]={sm[i][0],sm[i][1],sm[i][2]};
        sort(b,b+3);
        pos[a[i]]=i;
        if(b[0]==b[1]-1&&b[1]==b[2]-1){
            ll id[3]={0,0,0};
            rep(j,0,2){
                rep(k,0,2){
                    if(sm[i][k]==b[2]-j)id[j]=k;
                }
            }
            vector<ll>v;
            rep(j,0,2)v.push_back(id[j]);
            if(i&1){
                // reverse(v.begin(),v.end());
                if(!pos[id[0]])continue;
                ll rg=fl,lf=mp[v]+1;
                if(lf>rg)continue;
                if(sm[rg][id[0]]-sm[lf-1][id[0]])return puts("1"),void();
            }
            else mp[v]=i;
        }
    }
    return puts("2"),void();
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：saixingzhe (赞：5)

验题人题解。

# 分析

答案不超过 $2$ 是显然的，因为一定可以通过修改两人的第一张牌满足题目要求。

判断答案为 $0$ 根据题意模拟即可。

规定 $1\leq x$。

考虑如和判断答案是否可以为 $1$，发现当她出完此轮牌时各颜色数量为 $x-1,x,x+1$ 时可以通过调整一次得到，将前面一张 $x+1$ 颜色的牌变为 $x-1$ 的颜色的牌即可。

然后我们考虑你不能在她前面达成获胜条件。

* 你先出现 $x,x,x$，她后出现 $x-1,x,x+1$，只需要将你出现 $x,x,x$ 情况前某一张 $x+1$ 颜色的牌变为 $x-1$ 的颜色的牌即可。
  
* 你先出现 $x-1,x,x+1$，她后出现 $x-1,x,x+1$，（注意你和她 $x-1,x,x+1$ 的颜色一一对应）只需要将你出现 $x-1,x,x+1$ 情况后，她出现 $x-1,x,x+1$ 前某一张 $x+1$ 颜色的牌变为 $x-1$ 的颜色的牌即可。

* 你先出现 $x-1,x,x+1$，再出现 $x,x,x$，她后出现 $x-1,x,x+1$，（注意你和她 $x-1,x,x+1$ 的颜色一一对应）只需要将你出现 $x-1,x,x+1$ 情况后，出现 $x,x,x$ 前某一张 $x+1$ 颜色的牌变为 $x-1$ 的颜色的牌即可。

* 你先出现 $x,x,x$，再出现 $x-1,x,x+1$，她后出现 $x-1,x,x+1$，（注意你和她 $x-1,x,x+1$ 的颜色一一对应）显然，此时无论如何不能通过只修改一张牌使得她先于你达成胜利条件。

对于最后一种情况进行大力分讨，记录你最先出现 $x,x,x$ 的位置，最后出现 $x-1,x,x+1$ 的位置，判断即可。

对于记录 $x-1,x,x+1$ 最后出现的位置有种不动脑的方法就是枚举 $x-1,x+1$ 的颜色，直接开 $6$ 个变量，简单判断即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[3];
string s,t;
int main(){
	cin>>T;
	while(T--){
		a[0]=a[1]=a[2]=0;
		bool fl=1;
		int t01=0,t02=0,t10=0,t12=0,t20=0,t21=0,p=INT_MAX;
		cin>>n>>s>>t;
		for(int i=0;i<n;i++){
			if(s[i]=='P')	a[0]++;
			if(s[i]=='V')	a[1]++;
			if(s[i]=='W')	a[2]++;
			if(a[0]==a[1]&&a[0]==a[2]){
				fl=0;
				break;
			}	
			if(t[i]=='P')	a[0]++;
			if(t[i]=='V')	a[1]++;
			if(t[i]=='W')	a[2]++;
			if(a[0]==a[1]&&a[0]==a[2]){
				p=i;
				break;
			}	
		}
		if(fl){
			a[0]=a[1]=a[2]=0;
			for(int i=0;i<n;i++){
				if(s[i]=='P')	a[0]++;
				if(s[i]=='V')	a[1]++;
				if(s[i]=='W')	a[2]++;
				if(a[0]-a[1]==2&&a[0]-a[2]==1&&p>t01){
					fl=0;
					break;
				}
				if(a[0]-a[2]==2&&a[0]-a[1]==1&&p>t02){
					fl=0;
					break;
				}
				if(a[1]-a[0]==2&&a[1]-a[2]==1&&p>t10){
					fl=0;
					break;
				}
				if(a[1]-a[2]==2&&a[1]-a[0]==1&&p>t12){
					fl=0;
					break;
				}
				if(a[2]-a[0]==2&&a[2]-a[1]==1&&p>t20){
					fl=0;
					break;
				}
				if(a[2]-a[1]==2&&a[2]-a[0]==1&&p>t21){
					fl=0;
					break;
				}
				if(t[i]=='P')	a[0]++;
				if(t[i]=='V')	a[1]++;
				if(t[i]=='W')	a[2]++;
				if(a[0]-a[1]==2&&a[0]-a[2]==1)	t01=i;
				if(a[0]-a[2]==2&&a[0]-a[1]==1)	t02=i;
				if(a[1]-a[0]==2&&a[1]-a[2]==1)	t10=i;
				if(a[1]-a[2]==2&&a[1]-a[0]==1)	t12=i;
				if(a[2]-a[0]==2&&a[2]-a[1]==1)	t20=i;
				if(a[2]-a[1]==2&&a[2]-a[0]==1)	t21=i;
			}
			if(fl)	printf("2\n");
			else	printf("1\n"); 
		}
		else	printf("0\n");
	}
	return 0;
}
```

---

## 作者：CJZJC (赞：4)

可以考虑把字符串 $s$，$t$ 按 $s_1 t_1 s_2 t_2 \dots s_n t_n$ 拼接，记为 $a$。为了方便表述，这里分别把 `PVW` 表示为 `012`。

### Subtask 0

我会暴力！可以直接在 $a$ 上进行 dfs，复杂度为 $O(3^{2n})$。

### Subtask 1

我会找性质！注意到答案只有可能是 $0,1,2$，因为在最坏情况下，只要 $2$ 次操作把 $a_1,a_2,a_3$ 改成互不相同的数就行了。

首先我们可以 $O(n)$ 判断答案是否为 $0$。接下来判断答案是否为 $1$，我们可以枚举修改哪个位置，再扫一遍 $a$ 就可以了。剩下的情况的答案必然为 $2$。总复杂度为 $O(n^2)$。

### Subtask 4

考虑在判断答案是否为 $1$ 的过程上优化，可以发现答案为 $1$ 时，设获胜的位置为 $i$，$s_{0/1/2}$ 表示 $a_1 \sim a_i$ 中 $0,1,2$ 出现的个数，则 $3 \mid i$ 且 $\{s0,s1,s2\}=\{\frac{i}{3}-1,\frac{i}{3},\frac{i}{3}+1\}$。于是我们就记录每个 $a_i$ 最后出现的位置。

但是，如果把某个位置修改后，自己比对手先赢，就会出现问题。于是，我们设 $lst_{i,j}$ 表示最前的把 $i$ 改为 $j$ 且不会出现这种情况的位置。每次出现 $3 \mid i$ 且 $\{s0,s1,s2\}=\{\frac{i}{3}-1,\frac{i}{3},\frac{i}{3}+1\}$ 时，如果 $i$ 为偶数，就把操作一次会赢的 $lst_{i,j}$ 清空，否则若 $i$ 为奇数，如果存在符合的 $lst_{i,j}$，答案就为 $1$。

最后，如果在自己在 $pos$ 位置不做操作就已经赢了，还需要满足 $lst_{i,j} \leq pos$。

这些都可以 $O(n)$ 维护。

代码：(这里的 $lst_{i,j}$ 进行了状态压缩)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define flush() fwrite(obuf,1,O-obuf,stdout)
#define putchar(x) ((O==obuf+(1<<21))&&(flush(),O=obuf)),*O++=x
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read() {
    register int x=0,f=1;register char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
    return x*f;
}
inline void write(register int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar((x%10)^48);
}
struct Flush{
    ~Flush(){flush();}
}_;
#define N 100010
int t,n,a[N*2],ans;
signed main(){
    int T;
    cin>>t;
    T=t;
    while(t--){
        ans=556676;
        cin>>n;
        for(int i=1;i<=2*n;i++){
            a[i]=0;
        }
        for(int i=1;i<=n;i++){
            char c;
            cin>>c;
            if(c=='P'){
                a[2*i-1]=0;
            }
            else{
                if(c=='V'){
                    a[2*i-1]=1;
                }
                else{
                    a[2*i-1]=2;
                }
            }
        }
        for(int i=1;i<=n;i++){
            char c;
            cin>>c;
            if(c=='P'){
                a[2*i]=0;
            }
            else{
                if(c=='V'){
                    a[2*i]=1;
                }
                else{
                    a[2*i]=2;
                }
            }
        }
            int s[3]={};
            for(int i=1;i<=2*n;i++){
                s[a[i]]++;
                if(s[0]==s[1]&&s[1]==s[2]){
                    if(i%2==1){
                        ans=0;
                    }
                    break;
                }
            }
            if(ans==0){
                cout<<0<<endl;
                continue;
            }
            s[0]=s[1]=s[2]=0;
            int pos=2*n;
            int lst[9]={};
            for(int i=1;i<=2*n;i++){
                if(i<=pos){
                    lst[a[i]*3+0]=lst[a[i]*3+1]=lst[a[i]*3+2]=i;
                }
                s[a[i]]++;
                if(i%2==0){
                    if(s[0]==s[1]&&s[0]==s[2]){
                        pos=min(pos,i);
                        continue;
                    }
                    if(s[0]==s[1]-1&&s[1]==s[2]-1){
                        lst[6]=0;
                    }
                    if(s[0]==s[2]-1&&s[2]==s[1]-1){
                        lst[3]=0;
                    }
                    if(s[1]==s[0]-1&&s[0]==s[2]-1){
                        lst[7]=0;
                    }
                    if(s[1]==s[2]-1&&s[2]==s[0]-1){
                        lst[1]=0;
                    }
                    if(s[2]==s[0]-1&&s[0]==s[1]-1){
                        lst[5]=0;
                    }
                    if(s[2]==s[1]-1&&s[1]==s[0]-1){
                        lst[2]=0;
                    }
                }
                else{
                    if(s[0]==s[1]-1&&s[1]==s[2]-1){
                        if(lst[6]&&lst[6]<=pos){
                            ans=1;
                            break;
                        }
                    }
                    if(s[0]==s[2]-1&&s[2]==s[1]-1){
                        if(lst[3]&&lst[3]<=pos){
                            ans=1;
                            break;
                        }
                    }
                    if(s[1]==s[0]-1&&s[0]==s[2]-1){
                        if(lst[7]&&lst[7]<=pos){
                            ans=1;
                            break;
                        }
                    }
                    if(s[1]==s[2]-1&&s[2]==s[0]-1){
                        if(lst[1]&&lst[1]<=pos){
                            ans=1;
                            break;
                        }
                    }
                    if(s[2]==s[0]-1&&s[0]==s[1]-1){
                        if(lst[5]&&lst[5]<=pos){
                            ans=1;
                            break;
                        }
                    }
                    if(s[2]==s[1]-1&&s[1]==s[0]-1){
                        if(lst[2]&&lst[2]<=pos){
                            ans=1;
                            break;
                        }
                    }
                }
            }
            if(ans==1){
                cout<<1<<endl;
            }
            else{
                cout<<2<<endl;
            }
    }
    return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：2)

先按题意暴力模拟，处理答案为 $0$ 的情况。

其次，我们通过修改两人的第一张卡牌一定可以使前三张卡牌颜色互异，故只需要判断是否可以只修改一张即可，否则答案为 $2$。

对于修改一张卡牌，考虑寻找某一她出牌的时刻。如果此时三种颜色的卡牌累计出现次数为 $(k,k+1,k+2)$，那么显然可以修改此时之前某张第三种卡牌为第一种达到目的。

有个问题：如果我在她之前也出现 $(k,k+1,k+2)$ 这种状态，且修改的卡牌位置在这一刻之前，那么我将先获胜。所以还需记录我出现这种状态的时刻来判定。

还有问题。我们还需保证修改的卡牌在我出现三张牌出现次数相等的情况之前。特判搞定。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i,x,y) for(ll i=x;i<=y;i++)

const ll N=2e5+10;
ll q,n,a[N];
string s1,s2;
map<char,ll> pa;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	pa['P']=1;
	pa['W']=2;
	pa['V']=3;
	cin>>q;

	while(q--) {
		cin>>n>>s1>>s2;
		n<<=1;

		rep(i,1,n) {
			if(i%2) a[i]=pa[s1[i>>1]];
			else a[i]=pa[s2[(i>>1)-1]];
		}

//		rep(i,1,n) cout<<a[i]<<' ';

//		system("pause");
		ll cnt1=0,cnt2=0,cnt3=0,p=N;
		bool f=0;

		rep(i,1,n) {
			if(a[i]==1) cnt1++;
			else if(a[i]==2) cnt2++;
			else cnt3++;

			if(cnt1==cnt2&&cnt2==cnt3) {
				if(i%2) {
					cout<<"0\n";
					f=1;
				}
				
				p=i;
				break;
			}
		}

		if(f) continue;

		cnt1=cnt2=cnt3=0;
		ll t12=0,t13=0,t21=0,t23=0,t31=0,t32=0;

		for(ll i=1;i<=n;i+=2) {
			if(a[i]==1) cnt1++;
			else if(a[i]==2) cnt2++;
			else cnt3++;

			if(cnt1-1==cnt2&&cnt2-1==cnt3&&p>t12){
				cout<<"1\n";
				f=1;
				break;
			}else if(cnt1-1==cnt3&&cnt3-1==cnt2&&p>t13){
				cout<<"1\n";
				f=1;
				break;
			}else if(cnt2-1==cnt1&&cnt1-1==cnt3&&p>t21){
				cout<<"1\n";
				f=1;
				break;
			}else if(cnt2-1==cnt3&&cnt3-1==cnt1&&p>t23){
				cout<<"1\n";
				f=1;
				break;
			}else if(cnt3-1==cnt1&&cnt1-1==cnt2&&p>t31){
				cout<<"1\n";
				f=1;
				break;
			}else if(cnt3-1==cnt2&&cnt2-1==cnt1&&p>t32){
				cout<<"1\n";
				f=1;
				break;
			}
			
			if(a[i+1]==1) cnt1++;
			else if(a[i+1]==2) cnt2++;
			else cnt3++;
			
			if(cnt1-1==cnt2&&cnt2-1==cnt3) t12=i;
			else if(cnt1-1==cnt3&&cnt3-1==cnt2) t13=i;
			else if(cnt2-1==cnt1&&cnt1-1==cnt3) t21=i;
			else if(cnt2-1==cnt3&&cnt3-1==cnt1) t23=i;
			else if(cnt3-1==cnt1&&cnt1-1==cnt2) t31=i;
			else if(cnt3-1==cnt2&&cnt2-1==cnt1) t32=i;
		}

		if(f==0) cout<<"2\n";
	}
}
```

---

## 作者：ダ月 (赞：1)

提供一个卡常的做法。

看到这个题，脑海里已经有了一个直观的 dp 做法，记 $f(n,P,V,W,0/1)$ 表示 `P` 当前有 $P$ 张，`V` 有 $V$ 张，`W` 有 $W$ 张，$0/1$ 表示当前是否是你进行操作。

在转移的时候时刻将一些不合法状态删除。不合法状态形如：$f(n,k,k,k,1)$，表示在你进行操作时，已经三张为同一颜色。

这么做复杂度显然是 $O(n^4)$。

同时我们注意到 $P+V+W$ 是一个定值，因此一个状态可以缺省掉。$f(n,P,V,0/1)$ 表示 `P` 当前有 $P$ 张，`V` 有 $V$ 张，`W` 有 $K-P-V$ 张，$K$ 表示当前一共有多少张卡牌。

这么做复杂度显然是 $O(n^3)$。

无脑部分结束，接下来观察性质：

- 答案不超过 $2$。

这个性质提示我们有效状态很少。记 $f(n,P',V',W',0/1)$ 表示当前 `P` 的数量比假设不进行任何操作时 `P` 的数量多 $P'$ 个，如果 $P'$ 是负数，那么是比不操作时少 $|P'|$个。$V',W'$ 同理。

因此总状态数是 $O(n)$ 的，直接转移是 $O(n)$。

但是因为这个常数有些大，是关于总颜色（本题有 $3$ 种颜色）数指数级别的，想要通过的话需要卡卡常。

```
int f[N][2][5][5][5];
const int inf=0x3f3f3f3f;
std::array<int,3>V[125];
int tp=0;
int mp[5][5][5];
void init(){
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			for(int k=0;k<5;k++)
				if((2-i)+(2-j)+(2-k)==0&&(abs(2-i)+abs(2-j)+abs(2-k))<=4)
					V[++tp]={i,j,k},mp[i][j][k]=1;
}
std::array<int,3> pre1[N],pre2[N];
void solve(){
	//don't forget to open long long
	int n;std::cin>>n;
	std::string s,t;std::cin>>s>>t;
	s=" "+s;t=" "+t;
	auto get=[&](char c)->int{
		if(c=='P')return 0;
		if(c=='V')return 1;
		return 2;
	};
	for(int i=1;i<=n;i++){
		pre1[i]=pre1[i-1];
		pre2[i]=pre2[i-1];
		pre1[i][get(s[i])]++;
		pre2[i][get(t[i])]++;
	}
	for(int i=0;i<=n;i++)memset(f[i],0x3f,sizeof(f[i]));
	f[0][1][2][2][2]=0;
	auto check=[&](int A,int B,int C)->bool{return A==B&&A==C;};
	auto cmin=[&](int &A,int B)->void{A=std::min(A,B);};
	for(int i=1;i<=n;i++){
		for(int o=1;o<=tp;o++){
			auto S=V[o];
			int p=f[i-1][1][S[0]][S[1]][S[2]];
			if(p>2)continue;
			cmin(f[i][0][S[0]][S[1]][S[2]],p);
			int A=S[0]-2+pre1[i][0]+pre2[i-1][0],
				B=S[1]-2+pre1[i][1]+pre2[i-1][1],
				C=S[2]-2+pre1[i][2]+pre2[i-1][2];
			if(p>1)continue;
			if(get(s[i])==0){
				if(S[0]>0&&mp[S[0]-1][S[1]+1][S[2]])
					cmin(f[i][0][S[0]-1][S[1]+1][S[2]],p+1);
				if(S[0]>0&&mp[S[0]-1][S[1]][S[2]+1])
					cmin(f[i][0][S[0]-1][S[1]][S[2]+1],p+1);
			}if(get(s[i])==1){
				if(S[1]>0&&mp[S[0]+1][S[1]-1][S[2]])
					cmin(f[i][0][S[0]+1][S[1]-1][S[2]],p+1);
				if(S[1]>0&&mp[S[0]][S[1]-1][S[2]+1])
					cmin(f[i][0][S[0]][S[1]-1][S[2]+1],p+1);
			}if(get(s[i])==2){
				if(S[2]>0&&mp[S[0]+1][S[1]][S[2]-1])
					cmin(f[i][0][S[0]+1][S[1]][S[2]-1],p+1);
				if(S[2]>0&&mp[S[0]][S[1]+1][S[2]-1])
					cmin(f[i][0][S[0]][S[1]+1][S[2]-1],p+1);
			}
		}
		for(int o=1;o<=tp;o++){
			auto S=V[o];
			int A=S[0]-2+pre1[i][0]+pre2[i][0],
				B=S[1]-2+pre1[i][1]+pre2[i][1],
				C=S[2]-2+pre1[i][2]+pre2[i][2];
			if(check(A,B,C))continue;
			int p=f[i][0][S[0]][S[1]][S[2]];
			if(p>2)continue;
			cmin(f[i][1][S[0]][S[1]][S[2]],p);
			if(p>1)continue;
			if(get(t[i])==0){
				if(S[0]>0&&mp[S[0]-1][S[1]+1][S[2]])
					cmin(f[i][1][S[0]-1][S[1]+1][S[2]],p+1);
				if(S[0]>0&&mp[S[0]-1][S[1]][S[2]+1])
					cmin(f[i][1][S[0]-1][S[1]][S[2]+1],p+1);
			}if(get(t[i])==1){
				if(S[1]>0&&mp[S[0]+1][S[1]-1][S[2]])
					cmin(f[i][1][S[0]+1][S[1]-1][S[2]],p+1);
				if(S[1]>0&&mp[S[0]][S[1]-1][S[2]+1])
					cmin(f[i][1][S[0]][S[1]-1][S[2]+1],p+1);
			}if(get(t[i])==2){
				if(S[2]>0&&mp[S[0]+1][S[1]][S[2]-1])
					cmin(f[i][1][S[0]+1][S[1]][S[2]-1],p+1);
				if(S[2]>0&&mp[S[0]][S[1]+1][S[2]-1])
					cmin(f[i][1][S[0]][S[1]+1][S[2]-1],p+1);
			}
		}
	}
	int ans=inf;
	for(int i=1;i<=n;i++){
		for(int o=1;o<=tp;o++){
			auto S=V[o];
			int A=S[0]-2+pre1[i][0]+pre2[i-1][0],
				B=S[1]-2+pre1[i][1]+pre2[i-1][1],
				C=S[2]-2+pre1[i][2]+pre2[i-1][2];
			if(check(A,B,C))
				ans=std::min(f[i][0][S[0]][S[1]][S[2]],ans);
		}
	}
	std::cout<<ans<<'\n';
}
```

代码极其卡常，仅供参考。

不过这么做可以做颜色数更多的情况。

---

## 作者：sbno333 (赞：0)

比较诈骗。

下把两个人得出牌序列按出牌顺序组成序列，奇数位置三色相同她赢，偶数我赢。

考虑对于前三张，这期间我没有赢的可能，但到第三张她有，考虑前三张互不相同即可。

这里发现前三张最多改两张她就能赢。

因此答案最高为二。

先判断零的情况，然后着重考虑一。

考虑到改一张她获胜，改之前她获胜那一步三种颜色的数量一定是三个连续自然数，证明的话考虑逆过程，三色数量相同的牌改一个颜色，形成这种。

但是要保证我不赢。

这之前有可能出现我是跟她一模一样的大小关系以及三个连续自然数（暂时不考虑我本来就赢）其他情况显然不会导致我赢。

这时候只能改这个节点和她当前节点中间的牌，由于牌增加，过程中一定三色牌都出现过，所以改中间能找到那个她和我节点中数量最多颜色的牌，把它改成数量最小的牌，此时我的最近决策不变，不赢，中间决策赢不了，她赢。

考虑我本来就能赢，决策点一定要在我第一次赢之前，然后按照上面的思路，找上一个与她的可能获胜点相似的我的可能相似点，在我胜利之后直接输出二。

在前面这时候要注意要判断是否可能中间没有想要的，如果有就是一，否则二。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000009];
int n;
int z[3][1000009];
bool pd(){
	z[0][0]=z[1][0]=z[2][0]=0;
	for(int i=1;i<=n;i++){
		z[0][i]=z[0][i-1];
		z[1][i]=z[1][i-1];
		z[2][i]=z[2][i-1];
		z[a[i]][i]++;
		if(z[0][i]==z[1][i]&&z[1][i]==z[2][i]){
			if((i/3)&1)
			return 1;
			else
			return 0;
		}
	}
	return 0;
}
void _main(){
	cin>>n;
	for(int i=1;i<=2*n;i+=2){
		char t;
		cin>>t;
		t=(t=='P'?0:t=='V'?1:2);
		a[i]=t;
	}
	for(int i=2;i<=2*n;i+=2){
		char t;
		cin>>t;
		t=(t=='P'?0:t=='V'?1:2);
		a[i]=t;
	}
	n*=2;
	if(pd()){
		cout<<0<<endl;
		return;
	}
	z[0][0]=z[1][0]=z[2][0]=0;
	int y;
	y=1e16;
	for(int i=1;i<=n;i++){
		z[0][i]=z[0][i-1];
		z[1][i]=z[1][i-1];
		z[2][i]=z[2][i-1];
		z[a[i]][i]++;
		if(z[0][i]==z[1][i]&&z[1][i]==z[2][i]){
			if(y==1e16)
			y=i;
		}
		if(i%3==0&&max(z[0][i],max(z[1][i],z[2][i]))-min(z[0][i],min(z[1][i],z[2][i]))==2){
			if((i/3)&1){
				int gg;
				gg=0;
				for(int j=1;j<i;j++){
					if(z[0][j]-z[0][i]==z[1][j]-z[1][i]&&z[1][j]-z[1][i]==z[2][j]-z[2][i]){
						gg=j;
					}
				}
				if(gg>y){
					cout<<2<<endl;
					return;
				}
				if(!y){
					cout<<1<<endl;
					return;
				}
				int kk;
				kk=0;
				if(z[1][i]>z[kk][i]){
					kk=1;
				}
				if(z[2][i]>z[kk][i]){
					kk=2;
				}
				for(int i=gg+1;i<=y;i++){
					if(a[i]==kk){
						cout<<1<<endl;
						return;
					}
				}
				cout<<2<<endl;
				return;
			}
		}
	}
	cout<<2<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：Hydrogen_Huang (赞：0)

## 题解：P11207「Cfz Round 9」Rose

### 题目分析

调着调着比赛就结束了，结果赛后一发就 Ａ 了···

感觉这是一道模拟题，还有很多种情况，代码也是挺长的。

每一次“她”出牌就计算一次最少要更改多少次。如果“我”下棋后我赢了，再考虑将我此时的牌在一开始就进行调换，那么当前牌堆情况就一定是最多的牌的数量是最少的牌的数量 $+2$。

所以如果后面“她”出牌时有最多的牌的数量比最小的牌的数量 $+2$，就可以将当前“我”赢牌的这种情况进行调换。

但是还有一种情况是虽然“我”调换了牌，但是在后面“她”出现那种情况前我已经赢了，这种情况也不行，所以需要特判。细节可以看代码。

### 代码
~~~cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll t,n;

string s1,s2;

ll a,b,c;
ll cnt1,cnt2;

void add(char x)
{
	if(x=='P')
		a++;
	else if(x=='V')
		b++;
	else 
		c++;
	return;
}

int ca,cb,cc;

void aadd(char x)
{
	if(x=='P')
		ca++;
	else if(x=='V')
		cb++;
	else 
		cc++;
	return;
}

ll mn;
ll re,each;
ll mo;

bool fg;

ll com(ll x,ll y,ll z)
{
	if(x<y)swap(x,y);
	if(y<z)swap(y,z);
	if(x<y)swap(x,y);
	re=mo=0;
	each=(x+y+z)/3;
	re+=x-each;//将x填平
	mo=x-each;
	if(mo>=y-z)
	{
		z=y;//将z与y填平
		return re;
	}
	
	z+=mo;
	re+=(y-z)/2;
	
	return re;
}

int findmx()
{
	if(a>b&&a>c)
		return 1;
	if(b>a&&b>c)
		return 2;
	return 3;
}

int findmn()
{
	if(a<b&&a<c)
		return 1;
	if(b<a&&b<c)
		return 2;
	return 3;
}

void work()
{
	cin>>n;
	cin>>s1>>s2;
	s1=" "+s1,s2=" "+s2;
	a=b=c=0;
	cnt1=0,cnt2=0;
	
	mn=LLONG_MAX;
	
	for(ll i=1;i<=2*n;i++)
	{
		if(i%2==1)//她的
		{
			cnt1++;
			add(s1[cnt1]);
			if(i%3==0)
			{
				mn=min(mn,com(a,b,c));
				if(a==b&&b==c)
				{
					cout<<mn<<"\n";
					return;
				}
			//	cout<<i<<" "<<mn<<"\n";
			}
		}
		else
		{
			cnt2++;
			add(s2[cnt2]);
			if(a==b&&b==c)
			{
				fg=false;
				int k1,k2;
				int ta=a,tb=b,tc=c;
				int tcnt1=cnt1,tcnt2=cnt2;
				for(int j=i+1;j<=2*n;j++)
				{
					if(j%2==1)//她的
					{
						cnt1++;
						add(s1[cnt1]);
						if(j%3==0)
						{
							if(max(a,max(b,c))-min(a,min(b,c))==2)
							{
//特判
								k1=findmx();
								k2=findmn();
								
								ca=ta,cb=tb,cc=tc;
								
								if(k1==1)
									ca-=1;
								else if(k1==2)
									cb-=1;
								else
									cc-=1;
								
								if(k2==1)
									ca+=1;
								else if(k2==2)
									cb+=1;
								else
									cc+=1;
								int ccnt1=tcnt1,ccnt2=tcnt2;
								
								for(int k=i+1;k<=j;k++)
								{
									if(k%2==1)//她的
									{
										ccnt1++;
										aadd(s1[ccnt1]);
									}
									else
									{
										ccnt2++;
										aadd(s2[ccnt2]);
										if(ca==cb&&cb==cc)
										{
											cout<<mn<<"\n";
											return;
										}
									}
								}
								
								fg=true;
								break;
							}
						}
					}
					else
					{
						cnt2++;
						add(s2[cnt2]);
					}
				}
				if(fg)
				{
					cout<<min((ll)1,mn)<<"\n";
					return;
				}
				cout<<mn<<"\n";
				return;
			}
		}
	//	cout<<i<<" "<<a<<" "<<b<<" "<<c<<"\n";
	}
	cout<<mn<<"\n";
	return;
}
int main()
{
	cin>>t;
	while(t--)
	{
		work();
	}
	return 0;
}
~~~
代码有点长，码风有点怪，都是赛上修修补补出来ｄ的，有什么不懂的地方可以评论区里面问。

---


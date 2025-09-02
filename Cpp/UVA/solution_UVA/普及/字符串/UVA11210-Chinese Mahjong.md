# Chinese Mahjong

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2151

[PDF](https://uva.onlinejudge.org/external/112/p11210.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/00db9c6ee014cb07d2ff71e0aff3d224225bbbd1.png)

## 样例 #1

### 输入

```
1S 1S 2S 2S 2S 3S 3S 3S 7S 8S 9S FA FA
1S 2S 3S 4S 5S 6S 7S 8S 9S 1T 3T 5T 7T
0```

### 输出

```
Case 1: 1S 4S FA
Case 2: Not ready```

# 题解

## 作者：Luan_233 (赞：3)

## Solution

+ 每年过年都打麻将的我来发一发题解。

+ 这题有毒的输入输出都不必多说了，注意行末不要有多余的空格即可。我们发现答案不超过34，所以我们考虑枚举答案。对于每一种牌（饼子，条子，万子，风头，中发白）记录一个张数，再枚举所有的将牌（对），深搜搜出所有的“刻子”以及“顺子”，当某一类牌的张数不为3的倍数时不合法，当搜索深度超过4即为合法答案。注意回溯时各种奇奇怪怪的边界问题以及输出时的字符串的锅，因为数据水，所以就这样过了。

## Code
```
#include<string>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<algorithm>

#define N 15

using namespace std;

int W[N],T[N],S[N],F[N],H[N],tot,cnt;

inline bool dfs(int deep){
    if(deep>=4) return true;
    if((W[0]%3)||(T[0]%3)||(S[0]%3)||(F[0]%3)||(H[0]%3)) return false;
    for(int i=1;i<=9;i++){
        if(W[i]>=3){
            W[i]-=3; if(dfs(deep+1)){ W[i]+=3; return true; } W[i]+=3;
        }
        if(T[i]>=3){
            T[i]-=3; if(dfs(deep+1)){ T[i]+=3; return true; } T[i]+=3;
        }
        if(S[i]>=3){
            S[i]-=3; if(dfs(deep+1)){ S[i]+=3; return true; } S[i]+=3;
        }
        if(F[i]>=3){
            F[i]-=3; if(dfs(deep+1)){ F[i]+=3; return true; } F[i]+=3;
        }
        if(H[i]>=3){
            H[i]-=3; if(dfs(deep+1)){ H[i]+=3; return true; } H[i]+=3;
        }
    }
    for(int i=1;i<=7;i++){
        if((W[i]>0)&&(W[i+1]>0)&&(W[i+2]>0)){
            W[i]--,W[i+1]--,W[i+2]--;
            if(dfs(deep+1)){ W[i]++,W[i+1]++,W[i+2]++; return true; }
            W[i]++,W[i+1]++,W[i+2]++;
        }
        if((T[i]>0)&&(T[i+1]>0)&&(T[i+2]>0)){
            T[i]--,T[i+1]--,T[i+2]--;
            if(dfs(deep+1)){ T[i]++,T[i+1]++,T[i+2]++; return true; }
            T[i]++,T[i+1]++,T[i+2]++;
        }
        if((S[i]>0)&&(S[i+1]>0)&&(S[i+2]>0)){
            S[i]--,S[i+1]--,S[i+2]--;
            if(dfs(deep+1)){ S[i]++,S[i+1]++,S[i+2]++; return true; }
            S[i]++,S[i+1]++,S[i+2]++;
        }
    }
    return false;
}

inline bool check(){
    for(int i=1;i<=9;i++){
        if(T[i]>=2){
            T[i]-=2,T[0]-=2; if(dfs(0)){ T[i]+=2,T[0]+=2; return true; } T[i]+=2,T[0]+=2;;
        }
        if(W[i]>=2){
            W[i]-=2,W[0]-=2; if(dfs(0)){ W[i]+=2,W[0]+=2; return true; } W[i]+=2,W[0]+=2;
        }
        if(S[i]>=2){
            S[i]-=2,S[0]-=2; if(dfs(0)){ S[i]+=2,S[0]+=2; return true; } S[i]+=2,S[0]+=2;
        }
    }
    for(int i=1;i<=4;i++){
        if(F[i]>=2){
            F[i]-=2,F[0]-=2; if(dfs(0)){ F[i]+=2,F[0]+=2; return true; } F[i]+=2,F[0]+=2;
        }
    }
    for(int i=1;i<=3;i++){
        if(H[i]>=2){
            H[i]-=2,H[0]-=2; if(dfs(0)){ H[i]+=2,H[0]+=2; return true; } H[i]+=2,H[0]+=2;
        }
    }
    return false;
}

char ans[35][N];

inline void solve(){
    memset(ans,0,sizeof(ans));
    cnt=0; tot++;
    cout<<"Case "<<tot<<": ";
    T[0]++;
    for(int i=1;i<=9;i++){
    	if(T[i]==4) continue;
        T[i]++; if(check()) ans[++cnt][0]=(i+'0'),ans[cnt][1]='T'; T[i]--;
    }
    T[0]--;
    S[0]++;
    for(int i=1;i<=9;i++){
    	if(S[i]==4) continue;
        S[i]++; if(check()) ans[++cnt][0]=(i+'0'),ans[cnt][1]='S'; S[i]--;
    }
    S[0]--;
    W[0]++;
    for(int i=1;i<=9;i++){
    	if(W[i]==4) continue;
        W[i]++; if(check()) ans[++cnt][0]=(i+'0'),ans[cnt][1]='W'; W[i]--;
    }
    W[0]--;
    F[0]++;
    F[1]++; if(F[1]<=4&&check()) ans[++cnt][0]='D',ans[cnt][1]='O',ans[cnt][2]='N',ans[cnt][3]='G'; F[1]--;
    F[2]++; if(F[2]<=4&&check()) ans[++cnt][0]='N',ans[cnt][1]='A',ans[cnt][2]='N'; F[2]--;
    F[3]++; if(F[3]<=4&&check()) ans[++cnt][0]='X',ans[cnt][1]='I'; F[3]--;
    F[4]++; if(F[4]<=4&&check()) ans[++cnt][0]='B',ans[cnt][1]='E',ans[cnt][2]='I'; F[4]--;
    F[0]--;
    H[0]++;
    H[1]++; if(H[1]<=4&&check()) ans[++cnt][0]='Z',ans[cnt][1]='H',ans[cnt][2]='O',ans[cnt][3]='N',ans[cnt][4]='G'; H[1]--;
    H[2]++; if(H[2]<=4&&check()) ans[++cnt][0]='F',ans[cnt][1]='A'; H[2]--;
    H[3]++; if(H[3]<=4&&check()) ans[++cnt][0]='B',ans[cnt][1]='A',ans[cnt][2]='I'; H[3]--;
    H[0]--;
    if(!cnt) cout<<"Not ready";
    for(int i=1;i<=cnt;i++){
    	cout<<ans[i];
    	if(i!=cnt) cout<<" ";
    }
    cout<<endl;
}

char pai[N];

inline bool readin(){
    memset(W,0,sizeof(W));
    memset(T,0,sizeof(T));
    memset(F,0,sizeof(F));
    memset(S,0,sizeof(S));
    memset(H,0,sizeof(H));
    for(int i=1;i<=13;i++){
        cin>>(pai+1);
        if((i==1)&&(pai[1]=='0')) return false;
        if(pai[2]=='W') W[0]++,W[pai[1]-'0']++;
        if(pai[2]=='T') T[0]++,T[pai[1]-'0']++;
        if(pai[2]=='S') S[0]++,S[pai[1]-'0']++;
        if(pai[1]=='D') F[0]++,F[1]++;
        if(pai[1]=='N') F[0]++,F[2]++;
        if(pai[1]=='X') F[0]++,F[3]++;
        if((pai[1]=='B')&&(pai[2]=='E')) F[0]++,F[4]++;
        if(pai[1]=='Z') H[0]++,H[1]++;
        if(pai[1]=='F') H[0]++,H[2]++;
        if((pai[1]=='B')&&(pai[2]=='A')) H[0]++,H[3]++;
    }
    return true;
}

int main(){
    while(readin()) solve();
    return 0;
}
```

---

## 作者：Parabola (赞：2)

### Part0.题外话

最近沉迷麻将，然后就写了一道麻将题（？）

然后这题规矩比较简单，没有什么变态和牌格式，甚至连
「役」，都没有

~~无役海底 国士十三面~~

### Part1.思路

所以说我们先把牌编号$[0,34)$

对应1t~9t , 1s~9s , 1w~9w , 东南西北中发白

然后数组$c[i]$代表编号为$i$的牌的出现次数

考虑一个碰，由三个一样的牌组成，若设这张牌为$num$，那$c[num]>=3$

同理一个顺子存在条件就是

有$c[num] , c[num + 1] , c[num + 2] >= 1$

当然$num$不能是字牌和9s,9t,9w,8s,8t,8w

然后我们每一张牌都枚举一次，加上原来的13张，检测是否和牌，如果和了就证明听这张。

最后唯一一点，如果各位打的是霓虹麻将的话，那么你要知道一点，中国麻将不允许虚听，也就是不能手上4张4t了还听4t

然后还有小细节，模拟要注意这些东西，可以看看Code

### Part2.Code

```cpp
#include<iostream>
#include<cstdio>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;

const int N = 14 + 5;

map <string , int> Num;
string s , tile[N] , tmp[N];
int Case , c[34];
bool flag;

const string Maj[] = {
	"1T" , "2T" , "3T" , "4T" , "5T" , "6T" , "7T" , "8T" , "9T" , 
	"1S" , "2S" , "3S" , "4S" , "5S" , "6S" , "7S" , "8S" , "9S" ,
	"1W" , "2W" , "3W" , "4W" , "5W" , "6W" , "7W" , "8W" , "9W" ,
	"DONG" , "NAN" , "XI" , "BEI" , "ZHONG" , "FA" , "BAI"
};

bool dfs(int step) {
	if(step == 4) return 1;
	for(int i = 0 ; i < 34 ; ++i)	
		if(c[i] >= 3) {
			c[i] -= 3;
			if(dfs(step + 1)) return 1;
			c[i] += 3;
		}
	for(int i = 0 ; i <= 24 ; ++i)
		if(i % 9 <= 6 && c[i] >= 1 && c[i + 1] >= 1 && c[i + 2] >= 1) {
			c[i] -= 1 , c[i + 1] -= 1 , c[i + 2] -= 1;
			if(dfs(step + 1)) return 1;
			c[i] += 1 , c[i + 1] += 1 , c[i + 2] += 1;
		}
	return 0;
}

bool check(int k) {
	memset(c , 0 , sizeof c);
	for(int i = 0 ; i < 13 ; ++i) ++c[Num[tile[i]]];
	++c[k];
	if(c[k] > 4) return 0;
	for(int i = 0 ; i < 34 ; ++i) {
		if(c[i] >= 2) {
			c[i] -= 2;
			if(dfs(0)) return 1;
			c[i] += 2;
		}
	}
	--c[k];
	return 0;
}

int main() {
	for(int i = 0 ; i < 34 ; ++i) Num[Maj[i]] = i;
	while(cin >> s && s != "0") {
		flag = 0;
		printf("Case %d:" , ++Case);
		tile[0] = s;
		for(int i = 1 ; i < 13 ; ++i) cin >> tile[i];
		for(int i = 0 ; i < 34 ; ++i)
			if(check(i)) cout << " " << Maj[i] , flag = 1;
		if(!flag) puts(" Not ready");
		else puts("");
	}
	return 0;
} 
```

---

## 作者：Micnation_AFO (赞：1)

**注意**：UVa 的输出格式向来很坑，本题中每一行的末尾都不能输出多余的空格。

**题目大意**：给你 $13$ 个麻将，让你判断加上哪些麻将之后能胡牌，仅考虑最简单的玩法。

**思路**：用数组 `cnt` 记录每种麻将的个数。对于每个数据，枚举所有麻将作为第 $14$ 张牌，并逐一判断。首先枚举所有对子将其从麻将序列中删除，然后用 `dfs` 判断剩下的序列是否合法。在判断顺子的时候要注意，虽然顺子都是连着的三个，但是类似于 `8T 9T 1S` 之类的组合，在程序中也会被判断成顺子，所以要加上特判。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define x 13
#define maxn 55
const string card[] = { "1T","2T","3T","4T","5T","6T","7T","8T","9T",
                        "1S","2S","3S","4S","5S","6S","7S","8S","9S",
                        "1W","2W","3W","4W","5W","6W","7W","8W","9W",
                        "DONG","NAN","XI","BEI","ZHONG","FA","BAI" };
map<string, int> m;
vector<string> v;
int cnt[maxn], i;
bool vis[maxn]; 

bool dis(int i) {//对于顺子的特判
    if (i == 7 || i == 8) return false;//判断 8T9T1S、9T1S2S 之类的不合法数据
    if (i == 16 || i == 17) return false;//同上
    if (i == 25 || i == 26) return false;//同上
    if (i > 26) return false;//超过 9W 就一定没有顺子
    return true;//显然这个函数可以简化，但貌似写成这样读者更好理解
}

void dfs(int num, string s) {//num 表示还剩的牌数，s 表示模拟到的字符串
    if (num == 0) { v.push_back(s); vis[m[s]] = true; return; }//加入答案并标记，防止重复访问
    for (int i = 0; i < 34; i++) {
        if (vis[m[s]] == true) return;//防止重复访问
        if (cnt[i] >= 3) {
            cnt[i] -= 3;
            dfs(num - 3, s);
            cnt[i] += 3;
        }
        if (vis[m[s]] == true) return;//同上
        if (cnt[i] && cnt[i + 1] && cnt[i + 2] && dis(i)) {
            cnt[i]--, cnt[i + 1]--, cnt[i + 2]--;
            dfs(num - 3, s);
            cnt[i]++, cnt[i + 1]++, cnt[i + 2]++;
        }
    }
}

void check(string s) {
    for (int i = 0; i < 34; i++) {
        if (cnt[i] >= 2) {
            cnt[i] -= 2;
            dfs(12, s);            
            cnt[i] += 2;
        }
    }
}

signed main() {
    for (int i = 0; i < 34; i++) m[card[i]] = i;
    while (1) {
        memset(cnt, 0, sizeof(cnt));
        memset(vis, 0, sizeof(vis));
        v.clear();
        for (int i = 1; i <= x; i++) {
            string s; cin >> s;
            if (s == "0") return 0;
            cnt[m[s]]++;
        }
        for (int i = 0; i < 34; i++) {
            if (cnt[i] >= 4) continue;
            cnt[i]++;
            check(card[i]);         
            cnt[i]--; 
        }
        cout << "Case " << ++i << ":";
        if (v.empty()) cout << " Not ready" << endl;
        else {
            for (vector<string> :: iterator it = v.begin(); it != v.end(); it++) cout << " "<< *it;
            cout << endl;
        }
    }
    return 0;
}

```



---

## 作者：Isshiki·Iroha (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/UVA11210)

这是一个麻将模拟题，只是没有特殊牌型（比如七对和十三幺），要我们求听哪些牌，我们只需要枚举每一个牌（当然不能一个牌拿 5 张），看能不能胡就可以了（用 DFS 来搜索）。

大部分解释在代码里面：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define ri reg int
using namespace std;
const int maxn=34;
//建立对应关系，用数字表示
//记住一定要按照题目给的输出牌的优先顺序打
//这个我调了好久
const string mj[maxn+2]= {
	"IAKIOI","1T","2T","3T","4T","5T","6T","7T","8T","9T",
	"1S","2S","3S","4S","5S","6S","7S","8S","9S",
	"1W","2W","3W","4W","5W","6W","7W","8W","9W",
	"DONG","NAN","XI","BEI","ZHONG","FA","BAI"
};
map<string,int>m;
int SSY[15]={0,1,9,10,18,19,27,28,29,30,31,32,33,34};
int Maj[maxn+2];
string temp[19];
inline void debug() {
	for(ri i(1); i<=maxn; ++i)cout<<Maj[i]<<" ";
	cout<<endl;
}
inline bool check(ri i) {
//判断从当前牌能否继续往后吃牌
// 比如 8T 后面是 9T 1S ，花色不同，不行
	if(i>=1&&i<=7)return true;
	else if(10<=i&&i<=16)return true;
	else if(19<=i&&i<=25)return true;
	else return false;
}
// Success 表示当前有几个能组的
// 比如现在有两个碰的牌 Success 就是 2
inline bool dfs(ri Success) {
	if(Success==4)return true;
	for(ri i(1); i<=maxn; ++i) {
		if(Maj[i]>=3) {//寻找能碰的牌
			Maj[i]-=3;
			if(dfs(Success+1))return true;
         //往下搜索
			Maj[i]+=3;
		}
	}
	for(ri i(1); i<=25; ++i) {//寻找吃牌
		if(check(i)&&Maj[i]>=1&&Maj[i+1]>=1&&Maj[i+2]>=1) {
			--Maj[i],--Maj[i+1],--Maj[i+2];
			if(dfs(Success+1))return true;
			++Maj[i],++Maj[i+1],++Maj[i+2];
		}
	}
	return false;
}
//判断特殊牌型，因为没有要求，所以没有改
inline bool Special_Judge() {
	bool flag2=false,ssy=false;
	for(ri i(1);i<=14;++i){
		if(Maj[SSY[i]]==0&&Maj[SSY[i]]>2)break;
		if(Maj[SSY[i]]==2){
			if(flag2==true)break;
			flag2=true;
		}
	}
	if(flag2==true)return true;
	int Cnt=0;
	for(ri i(1);i<=maxn;++i){
		if(Maj[i]==2)++Cnt;
		else if(Maj[i]!=0&&Maj[i]!=2)return false;
	}
	if(Cnt==7)return true;
	return false;
}
inline bool GetHead(ri M) {
	for(ri i(1); i<=maxn; ++i)Maj[i]=0;
	for(ri i(1); i<=13; ++i)++Maj[m[temp[i]]];
   //每一次都要清空和赋值
	++Maj[M];
	//if(Special_Judge())return true;
	if(Maj[M]>4)return false;
   //不能有 5 个一样的牌
	for(ri i(1); i<=maxn; ++i) {
    //找雀头，就是那个一对的
		if(Maj[i]>=2) {
			Maj[i]-=2;
			if(dfs(0))return true;
			Maj[i]+=2;
		}
	}
	--Maj[M];
	return false;
}
int main() {
	ios::sync_with_stdio(false);
	ri T=1;
	for(ri i(1); i<=maxn; ++i)m[mj[i]]=i;
	while(true) {
		cin>>temp[1];
		bool flag=false;
		if(temp[1]=="0")return 0;
		for(ri i(2); i<=13; ++i) {
			cin>>temp[i];
		}
		cout<<"Case "<<T++<<":";
		for(ri i(1); i<=maxn; ++i) {
			if(GetHead(i)) {
				flag=true;
				cout<<" "<<mj[i];
			}
		}
		if(flag==false)cout<<" Not ready";
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：破忆 (赞：1)

## 【题意】
**对子**：两张相同的牌

**刻子**：三张相同的牌

**顺子**：三张连续的牌

**听牌**：目前有14张手牌，能够拆分成一个对子和若干刻子或顺子

给出13张牌，判断第14张牌出现哪些牌名能够听牌

## 【分析】

首先把牌名映射成数字0~34

然后枚举第14张牌

由于每种牌名只有4张，枚举的牌不能超过3张

对于当前14张牌

依次枚举对子、刻子、顺子，判断是否能够听牌

## 【算法】
模拟
## 【代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
char str[40][10]={//打表映射
"1T","2T","3T","4T","5T","6T","7T","8T","9T",
"1S","2S","3S","4S","5S","6S","7S","8S","9S",
"1W","2W","3W","4W","5W","6W","7W","8W","9W",
"DONG","NAN","XI","BEI","ZHONG","FA","BAI"};
char s[10];
int tot;
int a[15];
int find(){
	for(int i=0;i<34;i++) if(!strcmp(s,str[i])) return i;
}
int num[40];
bool DFS(bool k,int s){//k表示是否有对子，s表示当前剩余牌数
	if(!s) return 1;//找到可行解
	if(!k){
		for(int i=0;i<34;i++)//对子
		if(num[i]>=2){
			num[i]-=2;
			if(DFS(1,s-2)) return 1;
			num[i]+=2;
		}
		return 0;
	}
	for(int i=0;i<34;i++)//刻子
	if(num[i]>=3){
		num[i]-=3;
		if(DFS(1,s-3)) return 1;
		num[i]+=3;
	}
	for(int j=0;j<=18;j+=9)
	for(int i=j;i<=j+6;i++)//顺子
	if(num[i]&&num[i+1]&&num[i+2]){
		num[i]--,num[i+1]--,num[i+2]--;
		if(DFS(1,s-3)) return 1;
		num[i]++,num[i+1]++,num[i+2]++;
	}
	return 0;
}
int main(){
	freopen("UVA11210.in","r",stdin);
	freopen("UVA11210.out","w",stdout);
	while(scanf("%s",s)!=EOF){
		if(s[0]=='0') break;
		printf("Case %d:",++tot);
		a[1]=find();
		for(int i=2;i<=13;i++){
			scanf("%s",s);
			a[i]=find();
		}
		bool flg=0;
		for(int i=0;i<34;i++){
			memset(num,0,sizeof num);
			for(int j=1;j<=13;j++) num[a[j]]++;
			if(num[i]>3) continue;
			num[i]++;
			if(DFS(0,14)){
				printf(" %s",str[i]);
				flg=1;
			}
			num[i]--;
		}
		if(!flg) printf(" Not ready");
		putchar(10);
	}
	return 0;
}
```


---

## 作者：SIGSEGV (赞：1)

我们半个机房已经中了[Majsoul](http://majsoul.com/1/)的毒了......

至少这道题不用去判什么“无役”

思路就是首先枚举听什么，然后从字牌往数牌推，并且枚举顺子，再弄一些奇奇怪怪的剪枝就好了

注意：
1. 如果你手上有4张相同的牌，你不能再听这张牌
2. 14张牌中有单张字牌一定和不了
3. 14张牌中有单张组不成顺子的数牌也和不了
4. 输出要按筒，索，万，东南西北，中發白的顺序输出（majsoul打多了就会按万，索，筒，东南西北，白發中的顺序输出）
5. UVA输出答案时貌似每行行末不能多空格
```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt[40];//1p~9p筒子 1s~9s索子 1m~9m万子 ESWN风牌 Chun中 Hatsu發 Haku白
char input[8];
const char name[][10] = {"DONG","NAN","XI","BEI","ZHONG","FA","BAI"},
           type[][10] = {"T","S","W"};//输出用
void add(char *s)
{
    if (isdigit(s[0])) //数牌
    {
        if (s[1] == 'W') ++cnt[s[0] - 30];//万
        else if (s[1] == 'T') ++cnt[s[0] - 48];//筒
        else ++cnt[s[0] - 39];//索
    }
    else
    {
        //四风
        if (s[0] == 'D') ++cnt[28]; 
        else if (s[0] == 'N') ++cnt[29];
        else if (s[0] == 'X') ++cnt[30];
        else if (s[0] == 'B')
        {
            if (s[1] == 'E') ++cnt[31];else ++cnt[34];//北和白
        }
        else if (s[0] == 'F') ++cnt[33];//發
        else ++cnt[32];//中
    }
}
//从字牌往前推
bool dfs(int pos = 34,bool has_pair = 0) 
{
    if (!pos) return has_pair;//有雀头才能和
    if (!cnt[pos]) return dfs(pos - 1,has_pair);//跳过这张牌
    if (pos > 27) //字牌
    {
        if (cnt[pos] == 2) //当对子
        {
            if (has_pair) return 0;else return dfs(pos - 1,1);
        }
        if (cnt[pos] == 3) return dfs(pos - 1,has_pair); //当刻子
        return 0; //单张或四张都和不了
    }
    if ((pos - 1) % 9 < 2) //数牌1/2
    {
        if (cnt[pos] == 2) //对子
        {
            if (!has_pair) return dfs(pos - 1,1);
            else return 0;
        }
        if (cnt[pos] == 3) return dfs(pos - 1,has_pair); //刻子
        return 0;
    }
    //数牌3~9
    if (cnt[pos] == 2 && !has_pair && dfs(pos - 1,1)) return 1; //当雀头能和 
    if (cnt[pos] == 3 && dfs(pos - 1,has_pair)) return 1; //当刻子能和
    int num = 0;
    while (cnt[pos] && cnt[pos - 1] && cnt[pos - 2]) //搜顺子
    {
        --cnt[pos];--cnt[pos - 1];--cnt[pos - 2];++num;
        if (cnt[pos] == 1 || (cnt[pos] == 2 && has_pair))
            continue;
        if (dfs(pos - 1,has_pair | (cnt[pos] == 2)))
        {
            cnt[pos] += num;cnt[pos - 1] += num;cnt[pos - 2] += num;//回溯（之后还要搜有没有听别的牌）
            return 1;
        }
    }
    cnt[pos] += num;cnt[pos - 1] += num;cnt[pos - 2] += num;//回溯（可能还能拆牌）
    return 0;
}
int main ()
{
    int _ = 0;
    while (1)
    {
        ++_;memset(cnt,0,sizeof(cnt));//牌数清零
        scanf("%s",input);
        if (input[0] == '0') break;
        printf("Case %d:",_);
        add(input);
        for (int i = 1;i <= 12;i++) scanf("%s",input),add(input);
        bool tinpai = 0;
        for (int i = 1;i <= 34;i++)
        {
            if (cnt[i] == 4) continue;//不能听手上有4张这种牌的牌
            if (i <= 27) //数牌
            {
                if (!cnt[i - 1] && !cnt[i] && !cnt[i + 1]) continue;//单张的凑不成顺子的数牌不搜
                ++cnt[i];
                if (dfs()) 
                    tinpai = 1,
                    printf(" %d%s",(i - 1) % 9 + 1,type[(i - 1) / 9]);
                --cnt[i];
            }
            else
            {
                if (!cnt[i]) continue;//单张字牌和不了
                ++cnt[i];
                if (dfs()) tinpai = 1,printf(" %s",name[i - 28]);
                --cnt[i];
            }
        }
        if (!tinpai) printf(" Not ready");
        putchar('\n');
    }
    return 0;
}
//送两组测试数据
//1S 1S 1S 2S 3S 4S 5S 6S 7S 8S 9S 9S 9S
//DONG DONG DONG NAN NAN NAN XI XI XI BEI BEI BEI FA
//第一组纯正九莲宝灯，听任意一种索子（有兴趣的可以自己拆牌）
//第二组大四喜+字一色，单骑听發
```

---

## 作者：残阳如血 (赞：0)

## 思路分析
一道~~大~~模拟。

一共只有 $34$ 种牌，因此可以一次判断是否“听”这些牌。比如，为了判断是否“听”一万，只需要判断自己拿到这张一万后能否可以继续和牌。这样，问题就转化成了给定 $14$ 张牌，判断是否可以和牌。为此，我们可以递归求解：首先将两张牌作为“将”，然后每次选 $3$ 张作为刻子或者顺子。

选将有 $5$ 种方法（一万、二万、三万、四万、五万都可以做将）。如果选五万做将，一万要么属于一个刻子，要么属于一个顺子。注意，这是不必考虑其他拍是如何形成刻子或者顺子的，否则会出现重复枚举。

为了快速选出将、刻子和顺子，我们用一个 $34$ 维向量来表示状态，即每种牌所剩余的张数。除了第一次直接枚举将牌之外，每次只需要就考虑编号最小的牌，看它是否形成刻子或者顺子，并且递归判断。但是本题有个陷阱，每一种牌只有 $4$ 张，所以 `1S1S1S1S` 是不“听”任何牌的。
## 程序实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const char *mahjong[] = {
	"1T", "2T", "3T", "4T", "5T", "6T", "7T", "8T", "9T",
	"1S", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S",
	"1W", "2W", "3W", "4W", "5W", "6W", "7W", "8W", "9W",
	"DONG", "NAN", "XI", "BEI",
	"ZHONG", "FA", "BAI"
};
int kase, c[34], mj[15];
bool ok;
char s[100];
int convert(char *s) { // 预处理
	for (int i = 0; i < 34; i++)
		if (!strcmp(mahjong[i], s))
			return i;
	return -1;
}
bool search(int dep) { // 回溯法递归
	for (int i = 0; i < 34; i++)
		if (c[i] >= 3) { // 刻子
			if (dep == 3) return true;
			c[i] -= 3;
			if (search(dep + 1)) return true;
			c[i] += 3;
		}
	for (int i = 0; i <= 24; i++)
		if (i % 9 <= 6 && c[i] >= 1 && c[i + 1] >= 1 && c[i + 2] >= 1) { // 顺子
			if (dep == 3) return true;
			c[i]--, c[i + 1]--, c[i + 2]--;
			if (search(dep + 1)) return true;
			c[i]++, c[i + 1]++, c[i + 2]++;
		}
	return false;
}
bool check() {
	for (int i = 0; i < 34; i++)
		if (c[i] >= 2) { // 将牌
			c[i] -= 2;
			if (search(0)) return true;
			c[i] += 2;
		}
	return false;
}
int main() {
	while (scanf("%s", s) == 1) {
		if (s[0] == '0') break;
		printf("Case %d:", ++kase);
		mj[0] = convert(s);
		for (int i = 1; i < 13; i++) {
			scanf("%s", s);
			mj[i] = convert(s);
		}
		ok = false;
		for (int i = 0; i < 34; i++) {
			memset(c, 0, sizeof(c));
			for (int j = 0; j < 13; j++) c[mj[j]]++;
			if (c[i] >= 4) continue; // 每张牌最多只有4张
			c[i]++; // 假设拥有这张牌
			if (check()) { // 如果“和”了
				ok = true; // 那么听这张牌
				printf(" %s", mahjong[i]);
			}
			c[i]--;
		}
		if (!ok) printf(" Not ready");
		puts("");
	}
	return 0;
}
```

---


# Card Game

## 题目描述

Alice 和 Bob 正在玩一个游戏。他们共有 $n$ 张编号从 $1$ 到 $n$ 的卡牌。游戏开始时，部分卡牌分配给 Alice，其余分配给 Bob。

编号为 $i$ 的卡牌能击败编号为 $j$ 的卡牌当且仅当 $i > j$，但有一个例外：编号 $1$ 的卡牌可以击败编号 $n$ 的卡牌。

游戏会持续进行，直到某一方没有卡牌为止。每一回合的操作如下：
1. Alice 从自己的卡牌中选择一张正面朝上放在桌上；
2. Bob 在看到 Alice 的卡牌后，从自己的卡牌中选择一张正面朝上放在桌上；
3. 如果 Alice 的卡牌击败 Bob 的卡牌，两张卡牌都由 Alice 收走；否则，两张卡牌都由 Bob 收走。

玩家可以使用之前回合中获得的卡牌。

在某一回合开始时没有卡牌的玩家输掉游戏。假设双方都采取最优策略，判断谁会获胜。

## 说明/提示

在第一个测试用例中，Alice 和 Bob 各有一张卡牌。由于 Alice 的卡牌能击败 Bob 的卡牌，她在第一回合后获胜。

在第二个测试用例中，Alice 和 Bob 各有一张卡牌。由于 Bob 的卡牌能击败 Alice 的卡牌，他在第一回合后获胜。

在第三个测试用例中，有两种可能的游戏进程：
- 如果 Alice 在第一回合出卡 $1$，Bob 可以用卡 $2$ 应对并收走两张卡。然后 Alice 必须在第二回合出卡 $3$，Bob 会用卡 $4$ 应对，最终 Bob 获胜；
- 如果 Alice 在第一回合出卡 $3$，Bob 可以用卡 $4$ 应对并收走两张卡。然后 Alice 必须出卡 $1$，Bob 可以用卡 $2$ 或卡 $3$ 应对，最终 Bob 获胜。

在第四个测试用例中，有两种可能的游戏进程：
- 如果 Alice 在第一回合出卡 $2$，Bob 可以用卡 $3$ 应对并收走两张卡。然后 Alice 必须在第二回合出卡 $4$，Bob 会用卡 $1$ 应对，最终 Bob 获胜；
- 如果 Alice 在第一回合出卡 $4$，Bob 可以用卡 $1$ 应对并收走两张卡。然后 Alice 必须出卡 $2$，Bob 可以用卡 $3$ 或卡 $4$ 应对，最终 Bob 获胜。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
2
AB
2
BA
4
ABAB
4
BABA
3
BAA
5
AAAAB
5
BAAAB
6
BBBAAA```

### 输出

```
Alice
Bob
Bob
Bob
Alice
Alice
Bob
Alice```

# 题解

## 作者：Judging_zhu (赞：4)

dmh 竟然发题解了，必须来写一篇。
### 思路
把 Alice 简化成 $A$，Bob 简化成 $B$
，第一张简化成“首”，最后一张简化成“尾”。

若 $A$ 有首有尾或 $A$ 有首无尾且 $B$ 只有尾一张，那么 $A$ 必赢。

若 $B$ 有首但是 $A$ 有末两张，那么还是 $A$ 必赢。

其他情况 $B$ 必赢。
### AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main() {
    cin>>t;
    while(t--){
        int n,find_A,find_B;
        string s;
        cin>>n>>s;
        find_A=find_B=0; 
        for(int i=0;i<n;i++)
        	if(s[i]=='B')find_B++;
        	//这个也可以用 s.find 替代 
		bool f;//f 为 1 时 A 赢 
		if(s[0]=='A'){//若 A 有第一张 
			if(s[n-1]=='A'||find_B==1)f=1;//若 A 有首有尾或 B 只有尾一张 A 必赢 
			else f=0;//否则输 
		}
		else {
			if(s[n-1]=='A'&&s[n-2]=='A')f=1;//若 B 有首但是 A 有最后两张必赢 
			else f=0;//否则必输 
		}
		cout<<(f?"Alice":"Bob")<<"\n";
    }
    return 0;
}
```

---

## 作者：dmh2012901 (赞：3)

### 题面

按数字大小，$$i > j$$ 时牌 $$i$$ 能打过牌 $$j$$。

唯一例外是牌 1 能打牌 $$n$$，形成一个“环”关系。

每一轮，先手 Alice 亮一张自己手里的牌，后手 Bob 才能回应（考试时没读题这里卡了好久）。

### 思路

首先，同时持有 $$1$$ 和 $$n$$ 的玩家，直接必胜。

其次，若被“拆散”了，谁在那对相邻的极端牌旁再握一张，谁就能形成“连环反复吃牌”的局面。

最后，若两边都无法做到拿下两张连牌，先手在劣势，后手可以反打。

具体见代码吧。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
int t,n,a,b;
char s[55];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin>>t;
	while(t--){
		a=b=0;
		cin>>n>>s+1;
		for(int i=1;i<=n;i++){
			if(s[i]=='B') b++;
			else a++;
		}
		if(s[1]=='B'){
			if(s[n]=='B') cout<<"Bob"<<endl;
			else{
				if(a==1) cout<<"Bob"<<endl;
				else if(s[n-1]=='A') cout<<"Alice"<<endl;
				else cout<<"Bob"<<endl;
			}
		}
		else{
			if(s[n]=='A') cout<<"Alice"<<endl;
			else{
				if(b==1) cout<<"Alice"<<endl;
				else if(s[n-1]=='B') cout<<"Bob"<<endl;
				else cout<<"Bob"<<endl;
			}
		}
	} 
    return 0;
}
```

---

## 作者：fire_star_ (赞：1)

分类讨论。

- Alice 有第 $1$ 张和第 $n$ 张，那么 Alice 必胜。因为唯一能击败第 $n$ 张牌的第 $1$ 张牌也在 Alice 手中，那么 Alice 手中的第 $n$ 张牌就是无敌的了。

- Alice 有除了第 $n$ 张外的所有张，这时 Alice 也是必胜的。因为 Alice 可以使用第 $1$ 张打败 Bob 的第 $n$ 张。

- 如果 Bob 有第一张，Alice 有最后两张，直接使用倒数第二张打败 Bob 的牌，于是 Alice 必胜。

- 其它情况均为 Bob 获胜。

  代码就不给出了。

---

## 作者：Aurelia_Veil (赞：1)

# 题解：CF2104C Card Game

分类讨论。

很容易想到，如果 Alice 有很大的卡牌，而且 Bob 没有更大的卡牌，那么 Alice 必胜。

因此，分类讨论即可。

首先，如果 Alice 有第一张和最后一张，Alice 必胜，因为唯一能打败最后一张的第一张也是 Alice 的。

还有，如果 Alice 除了最后一张都有，就可以用第一张打败最后一张，于是 Alice 必胜。

接着，如果 Bob 有第一张，但是 Alice 有最后两张，直接有倒数第二张打败 Bob 的牌，于是 Alice 必胜。

最后，其他情况 Bob 必胜。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		string a;
		cin>>a;
		int cnta=0,cntb=0;
		for(int i=0;i<n;i++){
			if(a[i]=='A'){
				cnta++;
			}else{
				cntb++;
			}
		}
		if(a[0]=='A'&&a[n-1]=='A'){
			printf("Alice");
		}else if(a[0]=='A'&&a[n-1]=='B'&&cntb==1){
			printf("Alice");
		}else if(a[0]=='B'&&a[n-1]=='A'&&a[n-2]=='A'){
			printf("Alice");
		}else{
			printf("Bob");
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Bobi2014 (赞：1)

### 思路

分类讨论：

- 如果一个人同时持有 $1$ 和 $n$，那么必胜。
- 如果不满足前面的条件且 Bob 掌握了第 $1$ 张和第 $n - 1$ 张或第 $n$ 张和其他任意一张，那么 Bob 必胜。
- 如果不满足前面的条件，那么 Alice 必胜。

这个思路是有反例的，就是牌的数量为 $2$ 的情况，这种情况特判一下就好了。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int Q,n,a_cnt,b_cnt;
char c[60];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> Q;
    while(Q --){
        cin >> n >> c;
        a_cnt = b_cnt = 0;
        for(int i = 0;i < n;i ++){
            if(c[i] == 'A'){
                a_cnt ++;
            }else{
                b_cnt ++;
            }
        }
        if(n == 2){
            if(c[0] == 'A' and c[1] == 'A'){
                cout << "Alice\n";
            }else if(c[0] == 'B' and c[1] == 'B'){
                cout << "Bob\n";
            }else if(c[0] == 'A' and c[1] == 'B'){
                cout << "Alice\n";
            }else{
                cout << "Bob\n";
            }
            continue;
        }
        if((c[0] == 'B' and c[n - 2] == 'B') or (c[n - 1] == 'B' and b_cnt > 1)){
            cout << "Bob\n";
        }else{
            cout << "Alice\n";
        }
    }
    return 0;
}
```

---

## 作者：AK_400 (赞：1)

首先，如果一个人同时有 $1$ 和 $n$ 那么他一定会赢。只需要一直出 $n$。

考虑一个人有 $1$ 没 $n$，另一个人有 $n$ 没 $1$ 的情况。

- Alice 没有 $n$ 时

如果 Bob 只有 $n$，那么 Alice 胜。

策略：只需要在第一轮出 $1$。

否则 Bob 胜。

策略：如果 Alice 出 $1$ 那么出任何一张不是 $n$ 的牌，否则出 $n$。 

- Bob 没有 $n$ 时

如果 Alice 有 $n-1$，那么 Alice 胜。

策略：每次出 $n-1$。

否则 Bob 胜。

策略：如果 Alice 出 $n$，那么出 $1$。否则出 $n-1$。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db long double
#define fls fflush(stdout)
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read2(a,b),read(c)
#define read4(a,b,c,d) read3(a,b,c),read(d)
#define read5(a,b,c,d,e) read4(a,b,c,d),read(e)
#define read6(a,b,c,d,e,f) read5(a,b,c,d,e),read(f)
int n;
string s;
void slv(){
    read(n);
    cin>>s;
    s=' '+s;
    if(s[1]=='A'&&s[n]=='A'){
        cout<<"Alice"<<endl;
        return;
    }
    if(s[1]=='B'&&s[n]=='B'){
        cout<<"Bob"<<endl;
        return;
    }
    if(s[1]=='A'){
        for(int i=2;i<n;i++){
            if(s[i]=='B'){
                cout<<"Bob"<<endl;
                return;
            }
        }
        cout<<"Alice"<<endl;
        return;
    }
    if(s[n-1]=='A'){
        cout<<"Alice"<<endl;
        return;
    }
    cout<<"Bob"<<endl;
}   
signed main(){
    int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

## 作者：zhangli828 (赞：0)

## 题目大意
有 $n$ 个数分别为 $0\sim n-1$，每一个 $i(i>j)$ 都可以干掉 $j$，但有一个特例—— $0$ 可以干掉 $n-1$。告诉你爱丽丝和鲍勃分别有哪些数，求最后谁可以赢。
## 题目解法
我们可以求出鲍勃数字的数量及其最大的数量，如果鲍勃没有数字或者只有一个数字但 $n$ 大于 $2$ 就输出 `Alice`。如果鲍勃只有一个数字并且 $n$ 等于 $2$，则 $0$ 是谁的数字谁就会赢。

然后我们遍历所有爱丽丝的数字，如果有一个数字不等于 $n-1$ 并且大于鲍勃最大的数字，则输出 `Alice`。最后如果最后一个数字和第一个数字全都是爱丽丝的，也要输出 `Alice`，剩下的情况鲍勃就可以赢了。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long
 
using namespace std;
 
int t, n, w, sum, flag;
string s;
 
signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--; sum = flag = 0) {
    cin >> n >> s, w = -1;
    for (int i = 0; i < n; i++) {
      (s[i] == 'B') && (w = i, sum++);
    }
    if ((sum < 2 && n > 2) || w < 0) {
      cout << "Alice\n";
      continue;
    } else if (sum == 1) {
      cout << (s[0] == 'A' ? "Alice\n" : "Bob\n");
      continue;
    }
    for (int i = 0; i < n - 1; i++) {
      if (s[i] == 'A' && i > w) {
        flag = 1;
      }
    }
    if (s[n - 1] == 'A' && s[0] == 'A') {
      flag = 1;
    }
    cout << (flag ? "Alice\n" : "Bob\n");
  }
  return 0;
}
```

---

## 作者：__hjyakioi__ (赞：0)

## 结论：最终的答案就是第一轮时获胜情况。
感性理解：
- 如果 alice 赢了第一轮：
alice 可以重复第一轮的策略，bob 无法反制，因为如果能反制 bob 会在第一轮就这么干，因为这样更优。
- 如果 bob 赢：
  同理，alice 相比第一轮时手牌更少，更弱势，自然无法赢。

注意特判 $1$ 与 $n$。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        vector<int> A, B;
        for (int i = 1; i <= n;i++){
            char c;
            cin >> c;
            if(c=='A')
                A.push_back(i);
            else
                B.push_back(i);
        }
        int awin = 0;//Alice能不能赢
        for(auto i:A){
            int beat = 0;//bob能不能反制
            for(auto j:B){
                if(i==1&&j!=n&&j>i)
                    beat = 1;
                if(i!=1&&i!=n&&j>i)
                    beat = 1;
                if(i==n&&j==1)
                    beat = 1;
            }
            awin |= !beat;
        }
        cout << (awin?"Alice":"Bob") << endl;
    }
}
```

---


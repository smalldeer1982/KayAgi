# [GCJ 2018 Qualification] Saving The Universe Again

## 题目描述

一个外星机器人正在威胁宇宙，它使用一束光束，能够摧毁所有的算法知识。我们必须阻止它！

幸运的是，我们已经了解了机器人的工作方式。它一开始拥有强度为 $1$ 的光束，并将运行一个由一系列指令组成的程序，这些指令会按从左到右的顺序依次执行。每条指令有以下两种类型之一：

- c（代表“充能”）：将光束的强度加倍。
- s（代表“发射”）：发射光束，造成等于当前光束强度的伤害。

例如，如果机器人的程序是 sccssc，当程序运行时，机器人会按如下方式执行：

- 发射光束，造成 $1$ 点伤害。
- 充能，将光束强度加倍至 $2$。
- 充能，将光束强度加倍至 $4$。
- 发射光束，造成 $4$ 点伤害。
- 发射光束，造成 $4$ 点伤害。
- 充能，将光束强度加倍至 $8$。

在这种情况下，程序总共会造成 $9$ 点伤害。

宇宙顶尖的算法专家们开发了一种护盾，最多可以承受 $\mathbf D$ 点总伤害。但机器人的当前程序在运行时可能会造成超过这个数值的伤害。

宇宙总统自愿飞入太空，在机器人运行程序之前对其进行黑客攻击。总统唯一能在不被机器人察觉的情况下进行的黑客手段，是交换两条相邻的指令。例如，总统可以通过交换上述程序的第三和第四条指令，将其变为 scscsc，这样总伤害就会降为 $7$。然后，总统还可以再次进行黑客操作，将程序变为 scsscc，总伤害降为 $5$，以此类推。

为了避免引起机器人的怀疑，总统不希望进行太多次黑客操作。请问，最少需要多少次黑客操作，才能确保程序造成的总伤害不超过 $\mathbf D$，如果无法做到，则输出 IMPOSSIBLE。

## 说明/提示

**样例解释**

注意，最后三个样例不会出现在测试集 1 中。

在样例 1 中，总统可以交换两条指令，将总伤害降为 $1$，护盾可以承受。

在样例 2 中，总统无需进行任何黑客操作，因为程序造成的总伤害为 $2$，护盾可以承受。

在样例 3 中，程序造成的伤害超过了护盾的承受能力，并且无论如何黑客都无法改变这一点。宇宙注定要毁灭。

样例 4 使用了题目描述中的程序。题目中演示了一种通过两次黑客操作将总伤害降为 $5$ 的方法。仅用一次黑客操作无法将伤害降至 $6$ 或以下；请记住，总统只能交换相邻的指令。

在样例 5 中，机器人永远不会发射，因此不会造成任何伤害，无需黑客操作。

在样例 6 中，需要进行五次黑客操作。注意，即使两次黑客操作交换的是同一对位置的指令，也算作两次操作。

**数据范围**

- $1 \leq T \leq 100$。
- $1 \leq D \leq 10^9$。
- $2 \leq P$ 的长度 $\leq 30$。
- $P$ 中的每个字符都是 $c$ 或 $s$。

**测试集 1（5 分，可见）**

机器人的程序中最多只包含 $0$ 个或 $1$ 个 $c$ 字符。

**测试集 2（10 分，隐藏）**

无额外限制。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
1 CS
2 CS
1 SS
6 SCCSSC
2 CC
3 CSCSS```

### 输出

```
Case #1: 1
Case #2: 0
Case #3: IMPOSSIBLE
Case #4: 2
Case #5: 0
Case #6: 5```

# 题解

## 作者：yangdezuo (赞：1)

## 解析
### 题目大意
通过最少的交换次数，使得造成的攻击小于等于护盾防御 $D$。

### 温馨提示
输入数据中，字符串 $P$ 均为大写字母。

### 方法
1. 首先要判断字符串 $P$ 中发射的数量，若大于护盾防御 $D$，则无论如何交换无法实现。

2. 而后，根据题目可知，当发射之前充能越多，造成的伤害越高，所以应该先把后面的发射往前移。所以应该从后往前找 ```CS``` 并将它们交换，重新计算伤害

3. 重复第二步操作直到造成的攻击小于等于护盾防御 $D$，此时交换次数即为答案。

**PS：** 在 string 类型定义的字符串中，可通过 ```rfind``` 直接实现从后往前寻找。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,d,cnt,sum,k,ans;
string s;
void calc(){
	k=1;
	cnt=sum=0;
	for(int i=0;i<s.size();i++){
		if(s[i]=='S') cnt++,sum+=k;
		else k<<=1;
	}
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>t;
	for(int o=1;o<=t;o++){
		cin>>d>>s;
		ans=0;
		calc();
		if(cnt>d){
			cout<<"Case #"<<o<<": IMPOSSIBLE\n";
			continue;
		}
//		cout<<sum<<endl;
		while(sum>d){
			int p=s.rfind("CS");
//			cout<<p<<' ';
			s[p]='S';
			s[p+1]='C';
			ans++;
			calc();
		}
		cout<<"Case #"<<o<<": "<<ans<<'\n';
	}
}
```

---

## 作者：yongqian123 (赞：1)

## 无脑打框架
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define io ios::sync_with_stdio(0), cin.tie(), cout.tie()
//
int T, D, c, s, y; //
string P;
void out(int x){
	//
	cout << "Case #" << x << ": " << y << '\n';
}
signed main(){
	io;
	cin >> T;
	for (int x = 1; x <= T; x++){
		//
		c = s = y = 0;
		cin >> D >> P;
		//
		out(x);
	}return 0;
}

```

## 分析
二进制。每个 `S` 前面有多少 `C`，$damage$（损害）就增加 $2$ 的多少次方。

发现每次都将最后一个 `CS` 交换，这是因为贪心，想要最大程度地减少 $damage$，这时 $damage$ 减少这个 `S` 对应的 $damage$ 的一半。

于是开一个 $p$ 数组存每个 `S` 对应的 $damage$。

```cpp
const int _P_l = 30;
int p[_P_l];
```

想让 $damage\le D$，循环：

```cpp
while (s > D){
	//
}if (s > D){cout << "Case #" << x << ": IMPOSSIBLE\n"; return;}
```

>穿插介绍一个函数 `rfind`，用于找最后一个……的首字符位置。
>
>如 `P.rfind("CS")` 返回最后一个 $\texttt{CS}$ 的 $\texttt{C}$ 的位置。

于是，`out` 函数就写好了：

```cpp
void out(int x){
	while (s > D){
		pos = P.rfind("CS");
		if (pos == string::npos){cout << "Case #" << x << ": IMPOSSIBLE\n"; return;}
		P[pos] = 'S', P[pos + 1] = 'C', s -= 1 << (p[pos] = p[pos + 1] - 1), p[pos + 1] = 0, y++;
	}if (s > D){cout << "Case #" << x << ": IMPOSSIBLE\n"; return;}
	cout << "Case #" << x << ": " << y << '\n';
}
```

别忘记清空 $p$：

```cpp
memset(p, 0, sizeof p);
```

## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define io ios::sync_with_stdio(0), cin.tie(), cout.tie()
const int _P_l = 30;
int T, D, c, s, y, pos, p[_P_l];
string P;
void out(int x){
	while (s > D){
		pos = P.rfind("CS");
		if (pos == string::npos){cout << "Case #" << x << ": IMPOSSIBLE\n"; return;}
		P[pos] = 'S', P[pos + 1] = 'C', s -= 1 << (p[pos] = p[pos + 1] - 1), p[pos + 1] = 0, y++;
	}if (s > D){cout << "Case #" << x << ": IMPOSSIBLE\n"; return;}
	cout << "Case #" << x << ": " << y << '\n';
}
signed main(){
	io;
	cin >> T;
	for (int x = 1; x <= T; x++){
		memset(p, 0, sizeof p);
		c = s = y = 0;
		cin >> D >> P;
		for (int i = 0; i < P.size(); i++) if (P[i] == 'C') c++; else s += 1 << c, p[i] = c;
		out(x);
	}return 0;
}

```

---

## 作者：shiziyu111 (赞：0)

# 题目大意

给定一串字符串，其中 ```S``` 代表发射（造成等同于当前攻击力的伤害，但不将攻击力清零，不清零！），```C``` 代表加强（将攻击力变为当前的两倍）。

你可以将两个相邻的字符交换，问最少交换多少次，能使最终伤害 $\le$ 防御力 $D$，如果无论如何都无法做到，输出 ```IMPOSSIBLE```。

# 分析

首先，我们先统计出各个攻击造成的伤害，及其伤害之和。

显然，伤害值相同的进攻意味着在字符串中连续的 ```S```。令 $a$ 为这组 ```S``` 之前的 ```C``` 的个数，$sum$ 为总伤害，则将这组 ```S``` 中最左边的那一个 ```S``` 与其之前的 ```C``` 进行交换，对 $sum$ 带来的贡献为 $(2^{a-1}-2^a)$，即 $-2^{a-1}$。

接下来，我们只需先判断能否做到（就是看每次攻击为 $1$ 时，能否比你的 $D$ 大），能做到时，再不断的贪心找最大的 $a$ 并减去 $2^{a-1}$，直至 $sum<D$，即可解决问题。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	for(int t=1;t<=T;t++)
	{
		int n,attack=0,attacks[30]={0},sum=0,d;;
		string a;
		cin>>d;
		cin>>a;
		int len=a.size();
		for(int i=0;i<a.size();i++)
		{
			if(a[i]=='C')
			{
				attack++;
			}
			else
			{
				attacks[attack]++;
				sum+=pow(2,attack);
			}
		}
		cout<<"Case #"<<t<<":";
		if(a.size()-attack>d)
		{
			cout<<"IMPOSSIBLE\n";
			continue;
		}
		int count=0;
		while(sum>d)
		{
			while(attacks[attack]==0)
			{
				attack--;
			}
			attacks[attack]--;
			attacks[attack-1]++;
			sum-=pow(2,attack-1);
			count++;
		}
		cout<<count<<"\n";
	}
	return 0;
}
```

---

## 作者：SatoruXia (赞：0)

考虑贪心。  
首先模拟，计算机器人初始打出的伤害。如果原本的伤害也打不穿护盾（即 $\le D$）就直接输出 $0$。  
否则，最小化更改步数使其 $\le D$。可以想到将一个充能后发射的操作（即一个子串 `CS`）替换成发射后充能（即一个子串 `SC`）可以使伤害减半。我们只要将 `C` 尽可能往后移，`S` 尽可能往前移就可以达到机器人打出的伤害都很低，而充能的高伤害都打不出来的效果。  
这应如何用贪心实现？答案显而易见：在护盾能够挡下伤害之前，从右到左扫描，每遇到 `CS` 子串就交换，直至再也不能交换为止。最后判断是否能够挡下即可。注意中途要设置计数器统计更改次数。  
代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
//计算伤害
int compute(const string& P) {
    int ans = 0;
    int strength = 1;
    //模拟
    for (char c : P) { //遍历字符串的一种写法
        if (c == 'C') strength *= 2;
        else ans += strength;
    }
    return ans;
}
int main() {
	int T, num = 0;
 	cin >> T;
  	while (T--) {
  		num ++; //计数器
	    int D;
	    string P;
        cin >> D >> P;
        int s = 0;
        int res = compute(P);
        //统计数量，使用贪心
        while (res > D) { //在伤害不超过要求之前
     	    bool flag = false; //初始化
          	for (int i = P.size() - 1; i > 0; i--) {
           		if (P[i] == 'S' && P[i - 1] == 'C') {
             	    swap(P[i], P[i - 1]); //交换
                  	s++; //统计操作次数
                   	flag = true;
                    res = compute(P); //再次计算
                    break;
           		}
            }
            if (!flag) break; //直至无法交换
        }
        //输出部分
        if (res <= D) cout << "Case #" << num << ": " << s << endl;
        else cout << "Case #" << num << ": IMPOSSIBLE" << endl;
    }
    return 0;
}
```

---

## 作者：goIdie (赞：0)

## 思路

贪心，模拟。

我们考虑如何交换能使伤害最小。很明显，当出现 `CS` 组合时我们需要交换，因为这样可以让此次的伤害减半。同时，`CS` 组合的位置越往后越好，因为越往后伤害越大，减半减去的伤害也就越多。

每次交换后计算总伤害（计算总伤害的过程可以直接模拟），如果小于 $D$ 就输出，否则继续找。如果找不到 `CS` 组合且总伤害仍大于 $D$ 就输出 `IMPOSSIBLE`。

具体细节见代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int cal(string s){//计算当前总伤害 
    int d=1,tot=0;
    for(char c:s) {
        if(c=='C'){
            d*=2;
        }
		else{ 
            tot+=d;
        }
    }
    return tot;
}
int T,d,tot,cnt;
bool f;
string s;
int main(){
    cin>>T;
    for(int t=1;t<=T;t++){
        cin>>d>>s;
        tot=cal(s),cnt=0,f=0;
        if(tot<=d){//无需交换的情况 
            cout<<"Case #"<<t<<": "<<0<<endl;
            continue;
        }
        while(1){
            f=0;
            for(int i=s.size()-2;i>=0;i--){//倒序找CS组合 
                if(s[i]=='C'&&s[i+1]=='S'){
                    swap(s[i],s[i+1]);
                    cnt++;
                    tot=cal(s);
                    f=1;//是否找到 
                    break;
                }
            }
            if(tot<=d){//总伤害小于d就跳出循环 
                break;
            }
            if(!f){//找不到了也跳出循环 
                break;
            }
        }
        if(tot<=d){
            cout<<"Case #"<<t<<": "<<cnt<<endl;
        }
		else{
            cout<<"Case #"<<t<<": IMPOSSIBLE"<<endl;
        }
    }
    return 0;
}
```

---

## 作者：yihang2011 (赞：0)

### [P13132 [GCJ 2018 Qualification] Saving The Universe Again](https://www.luogu.com.cn/problem/P13132)

字符串，前缀和题，需要模拟与贪心。

首先可以考虑计算原字符串的伤害值。

容易发现，对于每一个字符 `S`，记该字符之前的字符 `C` 的个数为 $a$，则其对于总伤害的贡献为 $2^a$。那么我们可以计算一个前缀和数组 $a$，$a_i$ 表示在第 $i$ 个字符之前字符 `C` 的个数，那么总伤害值就好算了。

继续，很容易想到，交换相邻的字符时，只有交换前一个字符 `C`，后一个字符 `S`，才能降低总伤害值。且可以发现，$a_i$ 越大，字符对伤害值的贡献越大。所以考虑倒序枚举。遇到子串 `CS` 就交换。对于第 $i$ 个字符 `C` 与第 $i + 1$ 个字符 `S`，交换所减少的伤害值应为 $2^{a_{i + 1} - 1}$，同时，还需要 $a_i \gets a_i - 1$。

同时，每次交换后可能会在当前 $i + 1$ 与 $i + 2$ 的位置产生新的 `CS` 子串，应该从 $i + 1$ 开始下一轮遍历。

时间复杂度 $O(Tn)$，其中 $n$ 表示字符串的长度。

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int T;
ll p2[40];
int a[40];

int solve(int d, string s) {
    ll sum = 0;
    s = " " + s;
    for (int i = 1; i < s.size(); i++) {
        a[i] = a[i - 1] + (s[i] == 'C');
        if (s[i] == 'S') {
            sum += p2[a[i]];
        }
    }
    if (sum <= d) {
        return 0;
    }
    int cnt = 0, precnt = -1;
    for (int i = s.size() - 2; i >= 1; i--) {
        if (s[i] == 'C' && s[i + 1] == 'S') {
            swap(s[i], s[i + 1]);
            cnt++;
            sum -= (p2[a[i + 1] - 1]);
            a[i]--;
            if (sum <= d) {
                return cnt;
            }
            i = i + 2;
        }
    }
    return -1;
}

int main() {
    cin >> T;
    p2[0] = 1;
    for (int i = 1; i <= 30; i++) {
        p2[i] = p2[i - 1] * 2;     
    }
    for (int i = 1; i <= T; i++) {
        int d; string s;
        cin >> d >> s;
        int ans = solve(d, s);
        printf("Case #%d: ", i);
        if (ans == -1) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}
```

[AC Record](https://www.luogu.com.cn/record/223446042)

---

## 作者：kobebraint (赞：0)

## 看题

要求通过最少次相邻交换，将总伤害降低到 $\leq D$。不能做到就输出 `IMPOSSIBLE`。

## 怎么做？

每个 $s$ 的伤害由前面所有 $c$ 的乘积决定，所以我们要尽量把 $c$ 向后移，减小 $c$ 的影响。  
首先，不断从右往左找 `cs`，换成 `sc`，每次交换后计算一次总伤害；如果伤害 $\leq D$，结束；如果无法再换，输出 `IMPOSSIBLE`。

## 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define copy(a,b) copy(begin(a),end(a),begin(b))
#define ld long double
#define dot(x) fixed<<setprecision(x)
#define foru(a,b,c) for(ll a=b;a<=c;a++)

ll T,d;
string p;

ll calc(string s){
    ll res=0,pw=1;
    for(auto c:s){
        if(c=='C') pw*=2;
        else res+=pw;
    }
    return res;
}

int main(){
    cin>>T;
    foru(t,1,T){
        cin>>d>>p;
        ll ans=0;
        while(1){
            if(calc(p)<=d) break;
            bool ok=0;
            for(ll i=p.size()-2;i>=0;i--){
                if(p[i]=='C'&&p[i+1]=='S'){
                    swap(p[i],p[i+1]);
                    ans++,ok=1;
                    break;
                }
            }
            if(!ok){
                ans=-1;
                break;
            }
        }
        cout<<"Case #"<<t<<": ";
        if(ans==-1) cout<<"IMPOSSIBLE"<<endl;
        else cout<<ans<<endl;
    }
    return 0;
}
```

---


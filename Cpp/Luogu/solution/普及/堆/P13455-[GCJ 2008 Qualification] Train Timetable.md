# [GCJ 2008 Qualification] Train Timetable

## 题目描述

一条铁路线有两个车站，A 和 B。列车可以在一天内多次往返于 A 和 B 之间。当一列列车从 A 到达 B（或从 B 到达 A）后，需要一定的时间才能准备好进行返程——这段时间称为周转时间。例如，如果一列列车在 12:00 到达，且周转时间为 0 分钟，则它可以在 12:00 立即出发。

列车时刻表给出了所有 A 到 B 和 B 到 A 之间的行程的出发和到达时间。铁路公司需要知道，为了使时刻表能够顺利运行，早上分别需要在 A 和 B 各准备多少列列车：每当有列车需要从 A 或 B 出发时，必须有一列已经准备好的列车在该站等候。铁路线中有会车段，因此列车的到达顺序不一定与出发顺序相同。列车不能执行时刻表上未列出的行程。

## 说明/提示

**数据范围**

**小数据集（5 分，测试点 1 - 可见）**

- $1 \leq N \leq 20$
- $0 \leq N_A, N_B \leq 20$
- $0 \leq T \leq 5$

**大数据集（20 分，测试点 2 - 隐藏）**

- $1 \leq N \leq 100$
- $0 \leq N_A, N_B \leq 100$
- $0 \leq T \leq 60$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5
3 2
09:00 12:00
10:00 13:00
11:00 12:30
12:02 15:00
09:00 10:30
2
2 0
09:00 09:01
12:00 12:02```

### 输出

```
Case #1: 2 2
Case #2: 2 0```

# 题解

## 作者：b_donk (赞：1)

### 题目大意
求出在两站早上分别需要**多准备**多少列车才能满足给定的时刻表运行需求。

### 题目思路
用贪心做即可。首先把给的字符串转换成时间并统一成分钟数，随后排序所有事件，时间少的优先，这样才能确保最后答案是最优解。最后模拟列车行驶过程计算各站点所需的最少准备列车数‌（详细模拟过程请看代码部分）。


### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M = 1e4+10;  // 定义最大事件数量常量
struct node {
	int time;      // 事件时间（分钟数）
	bool flag;     // 事件类型：true=出发事件，false=可用事件
	bool from_a;   // 事件所属车站：true=A站，false=B站
} nodes[M*2];      // 存储所有事件的数组

// 将给定的字符串转换为时间
int check(string s) {
	return stoi(s.substr(0,2))*60+stoi(s.substr(3,2));
}

bool cmp(node x, node y) {
	if(x.time != y.time) return x.time < y.time;
	return !x.flag;
}

int main() {
	int T;
	cin >> T;
	for(int x = 1; x <= T; x ++) {
		int cnt, na, nb;  // cnt=周转时间，na=A→B车次，nb=B→A车次
		cin >> cnt >> na >> nb;
		int res = 0;
		// 处理A→B方向车次
		for(int i = 0; i < na; i ++) {
			string dep, arr;  // 出发/到达时间字符串
			cin >> dep >> arr;
			nodes[res ++] = {check(dep), true, true};   // A站出发事件
			nodes[res ++] = {check(arr)+cnt, false, false}; // B站可用事件，这里+cnt是因为还要再周转
		}
		// 处理B→A方向车次
		for(int i = 0; i < nb; i ++) {
			string dep, arr;
			cin >> dep >> arr;
			nodes[res++] = {check(dep), true, false};  // B站出发事件
			nodes[res++] = {check(arr)+cnt, false, true};  // A站可用事件
		}
		// 排序所有事件, 时间优先
		sort(nodes, nodes+res, cmp);
		
		int c_a = 0, s_a = 0;  // c_a=A站可用列车数，s_a=A站需要多准备的列车
		int c_b = 0, s_b = 0;  // c_b=B站可用列车数，s_b=B站需要多准备的列车

		for(int i = 0; i < res; i ++) {
			if(nodes[i].flag) {
				if(nodes[i].from_a) {
					if(c_a) c_a--;  // A站有可用列车则消耗
					else s_a++;     // 否则增加
				} else {
					if(c_b) c_b--;  // B站同理
					else s_b++;
				}
			} else {
				if(nodes[i].from_a) c_a++;  // A站增加可用列车
				else c_b++;                 // B站增加可用列车
			}
		}
		cout << "Case #" << x << ": " << s_a << " " << s_b << '\n';
	}
	return 0;
}
```
### [AC记录](https://www.luogu.com.cn/record/227060814)

希望这篇题解能够帮助到你。

---

## 作者：lmz105 (赞：1)

### 思路
首先分别记录下每个时间（单位为分钟，下同）两个车站新增加的列车数量，接着从小到大遍历每个时间，算出这个时间两个车站的总列车数量分别是多少，因为车站的总列车数量不能为负，所以当某个车站的总列车数量小于 $0$ 时，该车站需准备的列车数量就要加上负的该车站的总列车数量，这样该车站的总列车数量就变成 $0$ 了，遍历完后，按格式输出答案即可。

### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
//#define rw() ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef rw()
#ifdef __linux__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

namespace Pv {
	template<typename T> inline void r(T &in) {
		in = 0;
		bool bo = 0;
		char ch = getchar();
		while (!isdigit(ch))
			bo ^= (ch == '-'), ch = getchar();
		while (isdigit(ch))
			in = (in << 1) + (in << 3) + (ch ^ 48), ch = getchar();
		if (bo)
			in = -in;
	}
	template<typename T> inline void w(T out) {
		static char op[25];
		int top = 0;
		if (out < 0) {
			putchar('-');
			do {
				op[++top] = -(out % 10) + 48, out /= 10;
			} while (out);
		} else {
			do {
				op[++top] = out % 10 + 48, out /= 10;
			} while (out);
		}
		while (top)
			putchar(op[top--]);
	}
	template<typename T, typename... Ts> inline void r(T &in, Ts &... ins) {
		r(in), r(ins...);
	}
	template<typename T, typename... Ts> inline void w(T out, Ts... outs) {
		w(out), w(outs...);
	}
	inline void w(const char *p) {
		while (*p) {
			putchar(*p++);
		}
	}
}
#undef getchar
#undef putchar
using namespace Pv;
#endif
using namespace std;
ll T,n,m,k,ans,ans1,a[26*60],b[26*60];
int main() {
	r(T);
	for (ll t=1;t<=T;t++){
		r(k,n,m);
		ans=ans1=0;
		set<ll>s;
		memset(a,0,sizeof a);
		memset(b,0,sizeof b);
		while(n--){
			ll x,y;
			r(x,y);
			a[x*60+y]--;
			s.insert(x*60+y);
			r(x,y);
			b[x*60+y+k]++;
			s.insert(x*60+y+k);
		}
		while(m--){
			ll x,y;
			r(x,y);
			s.insert(x*60+y);
			b[x*60+y]--;
			r(x,y);
			s.insert(x*60+y+k);
			a[x*60+y+k]++;
		}
		ll suma=0,sumb=0;
		for (auto i:s){
			suma+=a[i];
			sumb+=b[i];
			if (suma<0){
				ans-=suma;
				suma=0;
			}
			if (sumb<0){
				ans1-=sumb;
				sumb=0;
			}
		}
		w("Case #"),w(t),w(": "),w(ans),w(" "),w(ans1),w("\n");
	}
	return 0;
}
```

---

## 作者：Zjb13927701829 (赞：0)

# P13455 [Train Timetable](https://www.luogu.com.cn/problem/P13455) 题解
## 题目大意
本题模拟了一个列车调度系统，要求计算两个车站（$A$ 和 $B$）在一天的运营中需要准备的**最少列车数量**。

但是关键约束在于：
1. 列车到达后需经过**周转时间** $T$ 才能再次出发；
2. 行程顺序可能与到达顺序**不同**；
3. **必须**保证每次发车时车站有就绪列车。
## 算法设计
我们可以采用**双指针贪心算法**处理调度的整个过程：
1. **预处理阶段：**
- 将时间统一转换为分钟数便于计算；
- 对两站的出发行程**按时间升序排序**。
2. **动态调度阶段：**
- 使用两个指针分别跟踪两个车站的当前行程；
- 维护两个就绪队列（数组模拟）**记录可用列车**；
- 每次选择**当前时间更早的行程**处理。
3. **列车管理策略：**
- 检查就绪队列中**最早的列车**是否满足周转要求；
- 满足就重新用它，否则新增列车；
- **行程完成**后将列车加入**对面车站**的就绪队列。

## [AC](https://www.luogu.com.cn/record/232228632) Code
接下来展示我的代码，一些细节都写在注释里面了，请各位认真观看。
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

// 列车行程结构体
struct Tr {
    int dep;
    int arr;
};

const int MAX = 105; 
Tr ta[MAX], tb[MAX];
int ra[MAX], rb[MAX];
int ra_cnt = 0, rb_cnt = 0;

// 将时间字符串转换为分钟数
int toM(string t) {
    return stoi(t.substr(0,2))*60 + stoi(t.substr(3,2));
}

// 行程比较函数(按出发时间排序)
bool cmp(const Tr& a, const Tr& b) {
    return a.dep < b.dep;
}

// 有序插入数组(维护升序)
void ins(int a[], int& c, int v) {
    int i = c - 1;
    while (i >= 0 && a[i] > v) {
        a[i+1] = a[i];
        i--;
    }
    a[i+1] = v;
    c++;
}

// 核心调度算法
void sol(int T, int na, int nb) {
    // 对两个车站的行程按出发时间排序
    sort(ta, ta + na, cmp);
    sort(tb, tb + nb, cmp);
    
    int a = 0, b = 0; 
    int i = 0, j = 0; 
    
    // 重置就绪列车计数
    ra_cnt = 0;
    rb_cnt = 0;
    
    // 处理所有行程
    while(i < na || j < nb) {
        if(j == nb || (i < na && ta[i].dep <= tb[j].dep)) {
            // 检查A站是否有就绪列车可用
            if(ra_cnt > 0 && ra[0] + T <= ta[i].dep) {
                for(int k = 0; k < ra_cnt-1; k++) {
                    ra[k] = ra[k+1];
                }
                ra_cnt--;
            } else {
                // 需要新增列车
                a++;
            }
            // 该列车完成行程后加入B站就绪队列
            ins(rb, rb_cnt, ta[i].arr);
            i++;
        } else {
            // 处理B站出发的行程
            if(rb_cnt > 0 && rb[0] + T <= tb[j].dep) {
                for(int k = 0; k < rb_cnt-1; k++) {
                    rb[k] = rb[k+1];
                }
                rb_cnt--;
            } else {
                b++;
            }
            ins(ra, ra_cnt, tb[j].arr);
            j++;
        }
    }
    cout << a << " " << b << endl;
}

int main() {
    int N, T, na, nb;
    cin >> N; 
    
    for(int c = 1; c <= N; ++c) {
        cin >> T >> na >> nb; 
        string d, a;  
        
        // 读取A站行程
        for(int i = 0; i < na; ++i) {
            cin >> d >> a;
            ta[i] = {toM(d), toM(a)};
        }
        
        // 读取B站行程
        for(int i = 0; i < nb; ++i) {
            cin >> d >> a;
            tb[i] = {toM(d), toM(a)};
        }
        
        cout << "Case #" << c << ": ";
        sol(T, na, nb);  // 解决当前测试用例
    }
    return 0;
} //完结撒花

```

---

## 作者：rxr2018360074 (赞：0)

~~（标签里面有个堆误导性挺强的）（骗你的其实不强）~~

贪心，很明显的贪心了。

思路：首先，~~我们不收有小时和分钟两个变量的时间~~将读入的时间转化为分钟。接着我们看，如果你这一班车需要多准备一辆车才能满足的话，说明从对面来的所有车中没有一辆的**到达时间**加上**周转时间**比你这班的**出发时间**要早。

把条件转化一下，是不是就是说即使是对面来的**最早**的那班车的**到达时间**加上**周转时间**都比你的**出发时间**晚。

那么这时候就可以搬出我们的优先队列了，把塞进去的时间按照**到达时间从小到大**排序，每次只要查一下队头就可以。

同时，题目中说了“行程的顺序不一定按时间排序”，所以我们还要先对读入的数据按照**出发时间从小到大**排序，那么既然从小到大，两个站点又难以区分了，所以再加上一个 $flag$ 标记他是从哪个站出发即可。

代码：
```cpp
//提醒大家一下，尽早养成好好取变量名的习惯。
#include<bits/stdc++.h>
using namespace std;
struct no{
	int be,en;
	bool flag;
	bool operator <(const no &another)const{
		return en>another.en;
	}
};
bool cmp(no a,no b){
	return a.be<b.be;
}
no a[205];
int main(){
	int t;
	cin>>t;
	int ji=1;
	while(t--){
		priority_queue<no> a_q;
		priority_queue<no> b_q;
		int turn_time;
		cin>>turn_time;
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			int be_time;
			int en_time;
			int hour,minute;
			scanf("%d:%d",&hour,&minute);
			a[i].be=hour*60+minute;
			scanf("%d:%d",&hour,&minute);
			a[i].en=hour*60+minute;
			a[i].flag=0;
		}
		for(int i=n+1;i<=n+m;i++){
			int be_time;
			int en_time;
			int hour,minute;
			scanf("%d:%d",&hour,&minute);
			a[i].be=hour*60+minute;
			scanf("%d:%d",&hour,&minute);
			a[i].en=hour*60+minute;
			a[i].flag=1;
		}
		sort(a+1,a+n+m+1,cmp);
		int a_ans=0,b_ans=0;
		for(int i=1;i<=n+m;i++){
			if(a[i].flag==0){
				if(b_q.size()==0 || b_q.top().en+turn_time>a[i].be){
					a_q.push(a[i]);
					a_ans++;
				}
				else{
					a_q.push(a[i]);
					b_q.pop();
				}
			}
			else{
				if(a_q.size()==0 || a_q.top().en+turn_time>a[i].be){
					b_q.push(a[i]);
					b_ans++;
				}
				else{
					b_q.push(a[i]);
					a_q.pop();
				}
			}
		}
		cout<<"Case #"<<ji<<": "<<a_ans<<" "<<b_ans<<endl;
		ji++;
	}
	return 0;
}

``````

---


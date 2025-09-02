# [GCJ 2016 Qualification] Counting Sheep

## 题目描述

Bleatrix Trotter 这只羊发明了一种能帮助她更快入睡的方法。首先，她会选取一个数字 $\mathrm{N}$。然后，她依次念出 $\mathrm{N}$、$2 \times \mathrm{N}$、$3 \times \mathrm{N}$，以此类推。每当她念出一个数字时，她会思考这个数字中所有出现过的数字。她会记录下自己已经见过哪些数字（$0,1,2,3,4,5,6,7,8,9$），无论这些数字在她念出的哪一个数字中出现过。只要她已经见到过全部十个数字中的每一个至少一次，她就会入睡。

Bleatrix 必须从 $\mathrm{N}$ 开始，并且每次都要在念完 $i \times \mathrm{N}$ 后，直接念 $(i+1) \times \mathrm{N}$。例如，假设 Bleatrix 选择了 $\mathrm{N} = 1692$，她的计数过程如下：

- $\mathrm{N} = 1692$。现在她已经见过数字 $1,2,6$ 和 $9$。
- $2 \mathrm{N} = 3384$。现在她已经见过数字 $1,2,3,4,6,8$ 和 $9$。
- $3 \mathrm{N} = 5076$。现在她已经见过全部十个数字，于是她入睡。

她在入睡前最后念出的数字是多少？如果她会永远数下去，请输出 **INSOMNIA**。

## 说明/提示

**样例解释**

在第 1 组中，由于 $2 \times 0 = 0, 3 \times 0 = 0$，以此类推，Bleatrix 除了 $0$ 以外永远不会见到其他数字，因此她会永远数下去，无法入睡。可怜的羊！

在第 2 组中，Bleatrix 会依次念出 $1,2,3,4,5,6,7,8,9,10$。$0$ 是最后一个被见到的数字，因此她会在 $10$ 之后入睡。

在第 3 组中，Bleatrix 会念出 $2,4,6,\ldots$ 等等。在 $90$ 之前，她都不会见到数字 $9$，直到 $90$ 时才会见到，从而入睡。在此之前，她已经分别在 $10,10,2,30,4,50,6,70,8$ 这些数字中首次见到 $0,1,2,3,4,5,6,7,8$。

在第 4 组中，Bleatrix 会依次念出 $11,22,33,44,55,66,77,88,99,110$，然后入睡。

第 5 组就是题面描述中的例子。注意，这一组只会出现在大数据集，而不会出现在小数据集中。

**限制条件**

- $1 \leqslant \mathrm{T} \leqslant 100$。

**小数据集（7 分，测试集 1 - 可见）**

- $0 \leqslant \mathrm{N} \leqslant 200$。

**大数据集（8 分，测试集 2 - 隐藏）**

- $0 \leqslant \mathrm{N} \leqslant 10^{6}$。

翻译由 GPT4.1 完成。

## 样例 #1

### 输入

```
5
0
1
2
11
1692```

### 输出

```
Case #1: INSOMNIA
Case #2: 10
Case #3: 90
Case #4: 110
Case #5: 5076```

# 题解

## 作者：BlackHoles (赞：5)

### 正解（附证明）

当 $N = 0$ 时，容易发现无法达成目标。

当 $N > 0$ 时，结论：一定可以达成目标。

考虑证明：首先，每连续 $N$ 个正整数中，必有一个为 $N$ 的倍数。

我们尝试构造，设 $N$ 位数为 $k$，记 $123456789 \times 10^{k+1}$ 为 $a$，则有上面定理知 $a+1$ 到 $a+N$ 中必有一个为 $N$ 的倍数，且 $0$ 到 $9$ 在前面都存在，满足条件。

于是简单模拟即可，用 $flag_i$ 记录 $i$ 这个阿拉伯数字是否出现过，全部出现过即找到答案，输出即可。

### 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T, N;
bool flag[10];
int main(void) {
	cin.tie(0), cout.tie(0);
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		cin >> N;
		if (!N) {
			cout << "Case #" << t << ": INSOMNIA\n";
			continue;
		}
		memset(flag, false, sizeof flag);
		int num = 0, now = 0, tmp = 0;
		while (num < 10) {
			now += N;
			tmp = now;
			while (tmp) {
				int tot = tmp % 10;
				if (!flag[tot]) {
					flag[tot] = true;
					++num;
					if (num == 10) break;
				}
				tmp /= 10;
			}
		}
		cout << "Case #" << t << ": " << now << '\n';
	}
	return 0;
}
```
谢谢大家！（点个赞吧

---

## 作者：__szh_DNCB__ (赞：2)

蒟蒻的第四篇题解。

比较简单的模拟题。

注意到题目规定 $1 \le T \le 100$ 和 $0 \le N \le 10^6$，所以写一个 $O(TN)$ 的模拟就能够通过了。

具体地，我们可以用一个桶标记一下 0 到 9 是否都出现过（注意要用 memset 还原，我在这里吃过亏），如果都出现过了就输出最后一个数即可。数位拆分的方法可以参见 [B4065 数位和](https://www.luogu.com.cn/article/0umu2ym5)。

特别地，发现当且仅当输入的数字为 0 时，才会出现无解的情况，特判一下即可。GCJ 的输出一直都是非常需要注意，尤其对我这种 cout 党。我的[另一篇题解](https://www.luogu.com.cn/article/y4k4ibn7)也强调了这个输出的问题。

```code
#include<bits/stdc++.h>
using namespace std;
int m[10] = {};
bool check(){
	if (m[0] && m[1] && m[2] && m[3] && m[4] && m[5] && m[6] && m[7] && m[8] && m[9])return true;
	return false;
}
void solve(int Time){
	memset(m,0,sizeof m);
	int n;
	cin >> n;
	int num = n;
	if (n == 0){
		cout << "Case #" << Time << ": INSOMNIA\n";
		return;
	}
	
	int i = 1;
	int ans;
	while (true){
		int nu = num;
		while (nu){
			m[nu % 10] = 1;
			nu /= 10;
		}
		if (check()){
			ans = num;
			break;
		}
		i++;
		num = i * n;
	}
	cout << "Case #" << Time << ": " << ans << '\n';
}
int main(){
	int T;
	cin >> T;
	for (int i=1;i<=T;i++){
		solve(i);
	}
	return 0;
}
```

---

## 作者：Natural_Selection (赞：1)

# 题解：[P13185](https://www.luogu.com.cn/problem/P13185)

## 思路

很简单，挨个模拟 Bleatrix Trotter 这只羊数的数，用一个桶来存储，当 $1,2,3,4,5,6,7,8,9,0$ 全部出现时，输出当前模拟的数就行了。

对于输出 **INSOMNIA** 的情况，很明显，$\mathrm{N}$ 为 $0$ 时，可怜的 Bleatrix Trotter 一定睡不着。

蒟蒻在这里就提醒一句：**多测不清空，AC 去无踪。**

## [AC](https://www.luogu.com.cn/record/223505339) Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,t,b[11];
bool ch(){
    for(int i=0;i<=9;i++) if(b[i]==0) return false;
    return true;
}
int main(){
    cin>>t;
    while(t--){
        memset(b,0,sizeof(b));//多测要清空
        int n;
        cin>>n;
        printf("Case #%d: ",++k);
        if(n==0){
            cout<<"INSOMNIA"<<endl;
            continue;
        }
        int cnt=1;
        while(1){//模拟
            int tmp=n*cnt;
            while(tmp){
                b[tmp%10]++;
                tmp/=10;
            }
            if(ch()==true){
                cout<<n*(cnt)<<endl;
                break;//找到了
            }
            cnt++;
        }
    }
    return 0;
}
```

---

## 作者：yyz0526 (赞：0)

## 题目大意：
枚举 $N$ 的倍数， 直到全部十个数字都出现过为止。

## 思路：
显然，只有当 $N$ 为 $0$ 时，输出 `INSOMNIA`。

定义函数 $\operatorname{digit}$ 将每个 $N$ 的倍数进行拆分，并存入数组。

```cpp
bool num[10];
void digit(long long x){
	while(x>0){
		num[x%10]=true;
		x/=10;
	}
}
```

定义函数 $\operatorname{judge}$ 进行判断。

```cpp
bool num[10];
bool judge(){
	for(int i=0;i<10;i++){
		if(!num[i]){
			return false;
		}
	}
	return true;
}
```

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
bool num[10];
bool judge(){ // 判断是否全部出现。
	for(int i=0;i<10;i++){
		if(!num[i]){
			return false;
		}
	}
	return true;
}

void digit(long long x){ // 拆分数字。
	while(x>0){
		num[x%10]=true;
		x/=10;
	}
}

int main(){
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;i++){
		memset(num,0,sizeof(num)); // 清空。
		int n;
		long long cnt;
		scanf("%d",&n);
		if(n==0){ // 特判。
			printf("Case #%d: INSOMNIA\n",i);
			continue;
		}
		cnt=n;
        for(int j=1;;j++){
        	digit(cnt*j);
        	if(judge()){
        		printf("Case #%d: %d\n",i,cnt*j);
        		break;
			}
		}
	}
	return 0;
}
```

---

## 作者：_ByTT_ (赞：0)

# 题解：P13185 [GCJ 2016 Qualification] Counting Sheep
### 题意
给出整数 $N$ 与所有自然数从小到大依次相乘，得到的结果记录每个数位的数字，当 $0,1,2,3,4,5,6,7,8,9$ 都出现时，奶牛就可以睡着。

问奶牛睡前最后说的数是什么。如果奶牛永远睡不着，那么输出 `INSOMNIA`。
### 思路
模拟很简单，需要重点注意的是奶牛可能睡不着，于是我们可以用代码检测奶牛什么时候睡不着，然后在代码中特判，代码如下。
#### 检测代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[15];
signed main(){
	for(int i=1;i<=1000000;i++){
		memset(a,0,sizeof(a));
		for(int j=1;;j++){
			int x=i*j;
			while(x>0){
				a[x%10]++;
				x/=10;
			}
			bool flg=1;
			for(int w=0;w<10;w++){
				if(a[w]==0){
					flg=0;break;
				}
			}
			if(flg==1) break;
		}
		cout<<i<<'\n';
	}
	cout<<"w qwq xh qwq wls qwq";
	return 0;
}
```
运行后我们发现奶牛除了 $N$ 为 $0$ 时睡不着，其他时候总是可以睡着的。

那么唯一的问题解决了，按题意大模拟枚举即可。
### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[15];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T;cin>>T;
	for(int Tt=1;Tt<=T;Tt++){
		int n,ans;cin>>n;
		if(n==0){
			cout<<"Case #"<<Tt<<": INSOMNIA\n";
			continue;
		}
		memset(a,0,sizeof(a));
		for(int i=1;;i++){
			int x=i*n;
			ans=x;
			while(x>0){
				a[x%10]++;x/=10;
			}
			bool flg=1;
			for(int w=0;w<10;w++){
				if(a[w]==0){
					flg=0;break;
				}
			}
			if(flg==1) break;
		}
		cout<<"Case #"<<Tt<<": "<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：long_long_inf (赞：0)

# 思路

这题暴力枚举就行了。

首先，我们先处理不可能将所有数字都出现的情况。我相信每个人都会认为只有 $0$，但重点是证明。你可以将一百万的阶乘算出来，它包含了所有数字。而 $n$ 就一定是它的因数，所以如果前面都没有所有数字，到了这个数就一定有。

枚举就很简单了，用一个数组存每个数出现的次数，如果都出现了就停止。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[15];
void chai(int n) {
    while (n > 0) {
        a[n % 10]++;
        n /= 10;
    }
} //拆位
bool fun() {
    for (int i = 0; i <= 9; i++) if (!a[i]) return 0;
    return 1;
}
int main() {
    int t;
    cin >> t;
    for (int j = 1; j <= t; j++) {
        int n;
        cin >> n;
        cout << "Case #" << j << ": ";
        if (n == 0) {
            cout << "INSOMNIA" << endl;
            continue;
        }
        memset(a, 0, sizeof(a)); //初始化数组
        int x = n;
        while (!fun()) {
            chai(n);
            n += x;
        }
        cout << n - x << endl;
    }
    return 0;
}
```

[AC](https://www.luogu.com.cn/record/223692377)

---

## 作者：Pollococido (赞：0)

~~这么水的橙题居然是免费的！~~

## 题目大意
**多测**。多余每组测试点，找到最小的 $dif$，使得所有 $n \times i(i \in [1, dif])$ 中出现了 $0 \sim 9$ 的所有数字，永远无法完成输出 `INSOMNIA`。
## 解题思路
显然只有 $n = 0$ 只永远无法完成，接下来就暴力让 $dif \gets dif + 1$，用 bool 数组判断数字是否出现即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, kase, dif;
bool flg[15];

signed main() {
    cin >> t;
    while (t--) {
        cin >> n;
        dif = 0;
        memset(flg, false, sizeof flg);
        if (n == 0) cout << "Case #" << ++kase << ": " << "INSOMNIA" << endl;
        else {
            while (true) {
            	dif++;
                bool f = true;
                for (int i = 0; i <= 9; i++) {//不要写成 1 ~ 10 嘻嘻
                	//cout << flg[i] << " ";
                    if (!flg[i]) f = false;
                }//前面的是在判断数字是否都出现过
                //cout << endl;
                if (f) {
                    cout << "Case #" << ++kase << ": " << n * (dif - 1) << endl;//因为最后一次 dif++ 没有用上，所以 dif 要减一。
                    break;
                }
                int k = n * dif;
                while (k) {
                    flg[k % 10] = true;
                    k /= 10;
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：goIdie (赞：0)

## 思路

简单模拟。

首先明确一点，只有输入 $0$ 时，才会输出 `INSOMNIA`。

证明：我们知道，对于任意正整数 $k$，每连续 $k$ 个正整数中，必定存在一个 $k$ 的倍数。设 $k$ 为 $n$ 位数，那么在 $\left[ 123456789\times10^{n+1},123456789\times10^{n+1}+k\right]$ 中，必定存在 $k$ 的倍数。证毕。

上面这个证明只是证明在除 $0$ 以外的情况下一定会有一个 $k$ 的倍数包含 $\left[0,9 \right]$ 中的所有数字，即小羊不会永远数下去。

知道这一点，我们就可以直接模拟了。

依次计算 $N,2N,3N\dots$，每次计算后统计出现了哪些数字，开一个 map 来记录每个数字是否出现过。如果某次计算后所有数字都出现了，输出当前计算的数字即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k,q,now;
map<int,int>mp;
int main(){
    cin>>T;
    for(int t=1;t<=T;t++){
		mp.clear();
        cin>>n;
        if(!n){
            cout<<"Case #"<<t<<": INSOMNIA"<<endl;
            continue;
        }
        for(k=1;;k++){
            q=now=k*n;
            while(q){
                mp[q%10]=1;
                q/=10;
            }
            if(mp[0]&&mp[1]&&mp[2]&&mp[3]&&mp[4]&&mp[5]&&mp[6]&&mp[7]&&mp[8]&&mp[9]){
            	break;
			}
        }
        cout<<"Case #"<<t<<": "<<now<<endl;
    }
    return 0;
}
```

题外话：即使不知道上面这一引理，也可以设置一个比较大的数，比如 $1000$，当循环次数超过它时就可以直接退出循环并输出 `INSOMNIA` 了。

---

## 作者：_zhangshihao_ (赞：0)

### 思路
易证当 $N$ 为非负整数时都有解（即只有 $N=0$ 时无解），
则枚举 $N$ 前的系数，当 $[0,9]$ 中的数均出现过时跳出循环，具体实现见代码注释。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
bool f[15];
int main(){
	int T;
	scanf("%d",&T);
	int n,cnt,k;
	for(int i=1;i<=T;i++){
		memset(f,0,sizeof(f));
		cnt=0,k=1;//cnt为已经出现了多少个数字，k为系数
		scanf("%d",&n);
		printf("Case #%d: ",i);
		if(!n){//n=0时特判
			puts("INSOMNIA");
			continue;
		}
		while(cnt<10){
			int tmp=k*n;
			if(tmp%10==0&&!f[0]) f[0]=1,cnt++;//数字末尾为0时特判
			while(tmp){
				if(!f[tmp%10]) f[tmp%10]=1,cnt++;//若当前数字没有出现过则计数器加1
				tmp/=10;
			}
			k++;
		}
		printf("%d\n",(k-1)*n);
	}
	return 0;
}
```

---

## 作者：yangdezuo (赞：0)

## 解析
### 题目大意
输出每次输入的 $N$ 在每次变换后当十个数字都出现时的数字。

### 方法
可以通过简单的模拟，对每次操作后的数按位拆分，用一个数组记录出现过的数，当已经出现十个数字时输出当前的数。

通过观察样例，我们可以发现当输入 0 时，无论如何变换，永远为 0，此时应该输出 ```Case #x: INSOMNIA```。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x;
bool a[10];
bool check(){
	for(int i=0;i<=9;i++)
		if(!a[i]) return false;
	return true;
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>t;
	for(int o=1;o<=t;o++){
		cin>>n;
		if(n==0){
			cout<<"Case #"<<o<<": INSOMNIA\n";
			continue;
		}
		memset(a,0,sizeof(a));
		for(int i=1;!check();i++){
			x=i*n;
			int k=x;
			while(k){
				a[k%10]=true;
				k/=10;
			}
		}
		cout<<"Case #"<<o<<": "<<x<<'\n';
	}
}
```

---

## 作者：封禁用户 (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13185)
## 题目分析
希望审核大大给过。

挺水的一道模拟题，由于要计算是否每一个数字都出现过，所以考虑使用 `unordered_set`，可以不重复地记录数字，那么只需模拟，将所有的数字都拆分开，再进行记录即可 AC。

下面是题目代码。
## 题目[代码](https://www.luogu.com.cn/record/223504352)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0),cin.tie(0), cout.tie(0);
void solve(int N) {
	if(!N) {
		cout<<"INSOMNIA";
		return ;
	}
	unordered_set<char> v;
	int sum = 0;
	while(v.size() < 10) {
		sum += N;
		for(char c : to_string(sum))v.insert(c);//使用string记录可以更简便
	}
	cout<<sum;
}
signed main() {
	speed
	int T, N;
	cin >> T;
	for(int i=1; i<=T; ++i) {
		cin >> N;
		cout << "Case #" << i << ": ";
		solve(N) ;
		cout<< '\n';
	}
	return 0;
}

```

---


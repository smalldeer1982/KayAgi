# Vasya and Golden Ticket

## 题目描述

Recently Vasya found a golden ticket — a sequence which consists of $ n $ digits $ a_1a_2\dots a_n $ . Vasya considers a ticket to be lucky if it can be divided into two or more non-intersecting segments with equal sums. For example, ticket $ 350178 $ is lucky since it can be divided into three segments $ 350 $ , $ 17 $ and $ 8 $ : $ 3+5+0=1+7=8 $ . Note that each digit of sequence should belong to exactly one segment.

Help Vasya! Tell him if the golden ticket he found is lucky or not.

## 说明/提示

In the first example the ticket can be divided into $ 7 $ , $ 34 $ and $ 52 $ : $ 7=3+4=5+2 $ .

In the second example it is impossible to divide ticket into segments with equal sum.

## 样例 #1

### 输入

```
5
73452
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
1248
```

### 输出

```
NO
```

# 题解

## 作者：XUQING (赞：4)

这题的题意很简单。

大意是一个数字，能否拆分成k段，使得每一段的每一位数字相加结果相等。

一看数据量不大，脑子里第一个想法就是暴力搜索，瞎打一通，结果过了。

那么说下我的思路：

首先从头开始往后搜索，计算每一段子段的值，如果相同。则从该位置分割，将后面部分递归搜索。只需要在开头和结尾特判下即可。

搜索流程以样例举例子：
```
1. [7]  3452  			首先从头开始搜索 
2. [7]  [3]   452
3. [7]  [34]  52 		与上一段结果相同 开始下一段搜索
4. [7]  [34]  [5]  2
5. [7]  [34]  [52] 		搜索到头并且结果相同 找到答案
```
样例2:
```
1. [1]   248
2. [1]   [2]  48	   当前段的结果比上一段大，再搜索下去肯定也不对，回溯
3. [12]  48
4. [12]  [4]  8		   同2
5. [124] 8
6. [124] [8]		   搜索结束，无结果
```


代码如下：
```cpp
#include <iostream>
using namespace std;

int len;

// 计算总和
int sum(string s)
{
    int ans = 0;
    for(int i = 0; i < s.length(); i++)
    {
        ans += (s[i] - '0');
    }
    return ans;
}

// 字符串 总和 第几段
bool dfs(string s, int tot, int f)
{
    // 因为下面循环是以索引1开始搜索，这里特判下长度1的情况
    if(s.length() == 1 && s[0] - '0' == tot)
        return true;

    for(int i = 1; i <= s.length(); i++)
    {
        // 当前段总和
        int ans = sum(s.substr(0, i));

        // 搜索到头
        if(i == s.length() && ans == tot)
            return true;
        // 当前段大于上一段 再往下搜索没有意义 剪枝
        if(ans > tot && f)
            return false;

        // 当前段相等或是第一次搜索
        if(ans == tot || !f)
        {
            // 分割 搜索下一段
            bool b = dfs(s.substr(i, s.length()+1), ans, f + 1);
            if(b)
                return true;
        }
    }
    return false;
}


int main()
{
    cin >> len;

    string s;
    cin >> s;

    cout << (dfs(s,0,0)?"YES":"NO");

    return 0;
}
```

---

## 作者：lichenfan (赞：3)

这道题还是比较水的。  
黄金卡相加和相等可以通过枚举分成几段来考虑，我是直接暴力从 $n$ 到 $2$ 每种情况模拟一遍。   
### 主要模拟过程：
先定义一个 $ans$ 记录目前的一块的数，后面代码实现如下：
```cpp
if(sum%i==0){
	for(int j=1;j<=n;j++){
		ans+=a[j];                //块中数增加。
		if(ans==sum/i) ans=0;     //如果这个块与要求的相同，就继续记录下一个块。
		if(ans>sum/i) break;      //如果已经大于了，就直接结束，这不是一个可行的方案。
		if(j==n){ 
		cout<<"YES";              //如果所以块都齐了，就是可行的。（不用判断分出来的段数，以为总和不变）
		return 0; 
		}
	}
}
	
```
上面是这题的核心代码，下面放出全部的代码（注释在上方了）
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101],sum,n,ans;
int main(){
	cin>>n;
	string s;
	cin>>s;
	for(int i=1;i<=n;i++) a[i]=s[i-1]-'0',sum+=a[i];
	for(int i=2;i<=n;i++){
		ans=0;
		if(sum%i==0){
			for(int j=1;j<=n;j++){
			    ans+=a[j];
			    if(ans==sum/i) ans=0;
			    if(ans>sum/i) break;
			    if(j==n){
			    	cout<<"YES";
			    	return 0;
				}
			}
	 	}
	}
	cout<<"NO";
} 
```
如果我的题解还不够清楚，可以在评论区询问，一定回复。




---

## 作者：KillerXu (赞：2)

直接暴力即可，最大的和只可能是所有位数上的数相加，计算出相加的结果，然后令$k$从$0$到这个数循环，再去判断能否分成每段和为$k$。注意一点，题目要求分为两段及以上，所以要统计一下分成了几段。

## Code
```cpp
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>

#define N 105

using namespace std;

int n;
int a[N];

int main(){
	cin >> n;
	int sum = 0;
	for(int i = 1; i <= n; i++){
		char t;
		cin >> t;
		a[i] = t - '0';
		sum += a[i];//计算和
	}
	
	for(int k = 0; k <= sum; k++){
		int rec = 0 , t = 0 , flag = 1;//rec记录每段当前的和，t记录分成的段数，flag记录是否满足条件
		for(int i = 1; i <= n; i++){
			rec += a[i];//计算和
			if(rec == k){t++; rec = 0; continue;}//如果正好等于k，即可以分成一段，段数加一，每段和清零
			if(rec > k) {flag = 0; break;}//如果已经大于了，则没有可能等于了，直接跳出
		}
		if(flag && t > 1 && !rec) {cout << "YES"; return 0;}//如果满足所有条件，即flag为1,段数为两段及以上，rec已经被清零，输出YES
	}
	
	cout << "NO";//没有YES就输出NO
	
	return 0;
}
```

---

## 作者：liuzhongrui (赞：0)

~~放轻松，并不难。~~

首先，遍历所有可能的第一个分区段的长度 $len$。

现在，我们知道了这个长度，我们还可以计算每个段的和 $S$。

然后，使用贪心形成分区：从位置 $len + 1$ 开始，我们找到低于或等于 $S$ 的最大的前缀和，然后切割它，不断重复这个过程。

如果所有形成的段的和都等于 $S$，那么这是一个有效的分区，答案是 ```YES```。否则，没有有效的第一个段的长度，也没有有效的分区，因此答案是 ```NO```。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int main() {
	cin >> n >> s;
	int sum = 0;
	for(int i = 0; i < n - 1; ++i) {
		sum += s[i] - '0';
		bool flag = true;
		int pos = i + 1;
		int sum2 = 0;
		while(pos < n) {
			sum2 = s[pos++] - '0';
			while(pos < n && sum2 + s[pos] - '0' <= sum) {
				sum2 += s[pos] - '0';
				++pos;
			}
			if(sum2 != sum) flag = false;
		}
		if(sum2 != sum) flag = false;
		if(flag) {
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
```


---

## 作者：Ouaoan (赞：0)

题目：[Array Product](http://codeforces.com/contest/1042/problem/C)

题意：
给出一个序列（元素可负，可为0），以及两个操作：
一、合并两个元素，得到的元素在靠后的元素的位置，值为之前两个元素值的乘积。
二、删除一个元素（此操作**最多进行一次**）。
现要求输出任意一种操作，使得剩余的一个元素的值最大。

思路：
~~看了很久后~~可以得到：
一般的，0对答案没有贡献，可以全部删除。
如果负数的个数为偶数，那么这些负数可以全部保留。
如果负数的个数为奇数，那么就删掉**最大**的负数。
但是只允许删除一次，那么当有多个没有贡献的数时，就将他们先合并，再删除。
注意，当序列中没有相乘可得正数的数时，那么将没有贡献的数合并后所得的数**要保留**。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define read(x) scanf("%d",&x);
#define ll long long
#define maxn 200000

int n;
int a[maxn+5];
bool f[maxn+5];

void readin() {
	read(n);
	for(int i=1; i<=n; i++) {
		read(a[i]);
	}
}

vector<int> ans,vec;

int main() {
	readin();
	int flg=0,s=(-(1<<30)),w=0;
	for(int i=1; i<=n; i++) {
		if(a[i]<0) {
			if(a[i]>s) {
				s=a[i];
				w=i;
			}
			flg^=1;
		}
		if(a[i]==0) vec.push_back(i);
	}
	if(flg) {
		vec.push_back(w);
	}
	for(int i=0; i<vec.size(); i++) {
		f[vec[i]]=true;
		if(vec.size()-1==i) {
			if(vec.size()!=n) printf("2 %d\n",vec[i]);
		} else printf("1 %d %d\n",vec[i],vec[vec.size()-1]);
	}
	for(int i=1; i<=n; i++) {
		if(f[i]) continue;
		ans.push_back(i);
	}
	if(ans.size()) for(int i=0; i<ans.size()-1; i++) {
			printf("1 %d %d\n",ans[i],ans[ans.size()-1]);
		}
	return 0;
}
```

---

## 作者：KKarshilov (赞：0)

当时以为是个一眼题，事实证明确实是，然而忘了判0

~~连WA****发~~

题意就是给你一个数列，看看能不能划成几段，使得每段的和相等

一个显而易见的结论：必然有一段从1开始

从1开始的那段的和必然是一个前缀和

一共有n个前缀和

枚举前缀和然后判断即可

```cpp
#include <bits/stdc++.h>
using namespace std;


#define LL long long
#define db double

const int MAXN = 200;
const int LIM = 101;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    int ch = getchar();
    bool fg = false;
    for (x = 0; !isdigit(ch); ch = getchar()) {
        if (ch == '-') {
            fg = true;
        }
    }
    for (; isdigit(ch); ch = getchar()) {
        x = x * 10 + ch - '0';
    }
    if (fg) {
        x = -x;
    }
}

int n, a[MAXN], sum[MAXN];
char s[MAXN];

bool check(int x, int k) {
	int cur = k, tot = 1;
	for(int i = k + 1; i <= n; i++) {
		if(sum[i] - sum[cur] == x) {
			cur = i, tot++;
			while(sum[i] == sum[i + 1]) i++, cur++;
		}
		else while(sum[i + 1] == sum[i]) i++;
	}
	if(sum[n] - sum[cur] != x && cur != n) return 0;
	if(tot > 1) return 1;
	return 0;
}

signed main() {
	read(n);
	scanf("%s", s + 1);
	if(n == 1) {
		puts("NO");
		return 0;
	}
	for(int i = 1; i <= n; i++) a[i] = (int) (s[i] - '0');
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	for(int i = 1; i <= n; i++) {
		if(check(sum[i], i)) {
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
```

---

## 作者：NH2OIP (赞：0)

```pascal
var
  a:array[0..109]of int64;
  i,j,n,m:longint;
  w:ansistring;
  h:boolean=false;
begin
  readln(i);
  readln(w);
  a[0]:=0;n:=0;
  for i:=1 to length(w) do 
    if w[i]<>'0' then//去除所有的0以防止奇怪的事情发生
      begin
        inc(n);
        a[n]:=ord(w[i])-ord('0')+a[n-1];
      end;
  for i:=1 to n-1 do//枚举第一个串的长度
    if a[n] mod a[i]=0 then
      begin
        m:=i;
        for j:=i+1 to n do//判断
          if a[j]-a[m]=a[i] then m:=j
            else if a[j]-a[m]>a[i] then break;
        if m=j then begin h:=true; break;end;
      end;
  if h or(n=0){全零特判} then writeln('YES') else writeln('NO');
end.
```

---

## 作者：KagurazakaKano (赞：0)

这也是一道好题啊！

题目大意：给定$n$个长度为$1$的数列，要求是否可以将数列分成两段或多段，使得这些段相加都相等。

解析：如果要分成多段，那么假设分成$i$段，那么设$f$数组保存前缀和，必有$f_n \% i == 0$。

于是我们就有了以下贪心思想：如果不能放了就继续尝试，否则就输出$YES$。

### 注意：一定要特判全是0的情况！因为这个问题我第一次提交WA了。

```
#include <bits/stdc++.h>

using namespace std;

int a[105];

int f[105] = {0};

int main(){
	int n;
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		scanf("%1d",&a[i]);
		f[i] = f[i - 1] + a[i];  //计算前缀和
	}
	for(int i = 1; i <= n; i++){
		bool fg = 0;
		int cur = 0;
		int fni = f[n] / i;
		int C = f[n] % i;
		if((C == 0) && (fni != 0)){  //如果可以整除
			for(int j = 1; j <= n; j++){
				cur += a[j];
				if(cur > f[n] / i){
					fg = 1;
					break;
				} else {
					cur %= (f[n] / i);
				}
			}
			if(fg){
				continue;
			} else if((cur % (f[n] / i) == 0) && (i > 1)){  //说明有解
				printf("YES\n");
				return 0;
			}
		}
	}
	if((n >= 2) && (f[n] == 0)){
		printf("YES\n"); //特判
		return 0;
	} 
	printf("NO\n");
	return 0;
}
```

---

## 作者：_Qer (赞：0)

设分块数$k$，所有数和$sum$，则每块的数和为$sum/k$。所以我们就可以暴力枚举$k$（$k$取值为$[2,n]$，可以枚举），然后计算是否可以分成$k$段相等

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[110], sum;
//n,a如题,sum计算所有数之和
bool check(int s) {//每块的数和为s
    int tsum = 0;
    for (int i = 1; i <= n; ++i) {
        tsum += a[i];
        if (tsum == s) {//到这里可以分一块
            tsum = 0;
        } else if (tsum > s) {//此时当前块和不可能等于s
            return false;
        }
    }
    //可以不用判最后分的块数
    //假如每一块的和都为s，块数为sum/s，因s=sum/k，故sum/s=k
    return !tsum;
}
int main() {
    cin >> n;
    char c = getchar();
    while (c < '0' || c > '9')  c = getchar();
    for (int i = 1; i <= n; ++i) {
        a[i] = c - '0';
        sum += a[i];
        c = getchar();
    }//以上为输入
    for (int i = 2; i <= n; ++i) {//枚举块数
        if (sum % i == 0 && check(sum / i)) {
        	//假如sum%i!=0则不可能分成i个相等的块
            puts("YES");
            return 0;
        }
    }
    puts("NO");
    return 0;
}
```

---


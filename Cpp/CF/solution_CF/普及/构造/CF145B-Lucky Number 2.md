# Lucky Number 2

## 题目描述

Petya loves lucky numbers very much. Everybody knows that lucky numbers are positive integers whose decimal record contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya loves long lucky numbers very much. He is interested in the minimum lucky number $ d $ that meets some condition. Let $ cnt(x) $ be the number of occurrences of number $ x $ in number $ d $ as a substring. For example, if $ d=747747 $ , then $ cnt(4)=2 $ , $ cnt(7)=4 $ , $ cnt(47)=2 $ , $ cnt(74)=2 $ . Petya wants the following condition to fulfil simultaneously: $ cnt(4)=a_{1} $ , $ cnt(7)=a_{2} $ , $ cnt(47)=a_{3} $ , $ cnt(74)=a_{4} $ . Petya is not interested in the occurrences of other numbers. Help him cope with this task.

## 样例 #1

### 输入

```
2 2 1 1
```

### 输出

```
4774
```

## 样例 #2

### 输入

```
4 7 3 1
```

### 输出

```
-1
```

# 题解

## 作者：pikabi (赞：1)

来一发 vector 的（~~vector 大法好~~）

思索题面显然不能爆搜。但是看到 47 和 74 很容易得出，我们先把这 $nn$ 个 47 和 $mm$ 个 74 骨架搭好，再进一步往里填充多余的4 与 7 即可。

例如： 5 8 3 2 ----> 由于 $nn \ge mm$， 我们先有 474747 这个骨架，由于题目要求这个数最小（然鹅翻译没提到，望 update ），我们把剩余的 4 、7 填充， 4 放在最前面的 4 后， 7 放最后的 7 后，按此规律摆放即可。当搭骨架时，某些个数不够用了，就认为无解。当 $nn < mm$ 时同理。

特别注意的是，当 $nn = mm $ 时，可能 4 在开头行不通而 7 在开头可行，就需要进行两次判断了。

code-->

```cpp
#include <cstdio>
#include <vector>
#include <cmath>
#include <cctype>
#define PT 520

using namespace std;

int n, m, nn, mm, fl, kn, km, knn, kmm;

vector <int> a[2000006];//特别注意要开到 2*10^6 以上，不然会RE

int read()        
{        
    int s = 0, f = 1;        
    char ch = getchar();        
    while(!isdigit(ch)) {        
        if(ch == '-') f = -1;        
        ch = getchar();        
    }        
    while(isdigit(ch)) {        
        s = (s << 3) + (s << 1) + ch - '0';        
        ch = getchar();        
    }        
    return s * f;        
}        

int main(){
	kn = n = read(), km = m = read(), knn = nn = read(),kmm = mm = read();
	if(nn >= mm) {
		int k = nn + mm;
		a[1].push_back(1), --n; 
		for(int i = 2; i <= k + 1; i++){//here is 搭骨架
			if(i % 2 == 1){
				if(!mm || !n) {//第一次不行，跑到下面再来一次
					goto there;
				}
				a[i].push_back(1), --mm, --n;
			}
			else{	
				if(!nn || !m){//同上
					goto there;
					return 0;
				}
				a[i].push_back(2), --nn, --m; 
			}
		}
		while(n--){//here is 填充
			a[1].push_back(1); 
		}
		int w = k + 1;
		if(!(k % 2)) w--;
		while(m--){
			a[w].push_back(2); 
		}
		for(int i = 1; i <= k + 1; ++i)
		for(int j = 0; j < a[i].size() ; ++j)
		if(a[i][j] == 1)
		printf("4");
		else printf("7");
	}
	else {
		there:;//由于 coder 的懒惰，nn > mm 时也再跑了一次，但这无伤大雅
		n = kn, m = km, mm = kmm, nn = knn;//这里先回归原始条件
		for(int i = 1; i <= mm + nn + 1; ++i)
		a[i].clear() ;
		int k = nn + mm;
		a[1].push_back(1), --m; 
		for(int i = 2; i <= k + 1; i++){
			if(i % 2 == 1){
				if(!nn || !m) {
					printf("-1\n");
					return 0;
				}
				a[i].push_back(1), --nn, --m;
			}
			else{	
				if(!mm || !n){
					printf("-1\n");
					return 0;
				}
				a[i].push_back(2), --mm, --n; 
			}
		}
		while(n--){
			a[2].push_back(2); 
		}
		int w = k + 1;
		if(k % 2) w--;
		while(m--){
			a[w].push_back(1); 
		}
		for(int i = 1; i <= k + 1; ++i)
		for(int j = 0; j < a[i].size() ; ++j)
		if(a[i][j] == 1)
		printf("7");
		else printf("4");
	}
	return 0;
}
```

完结撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：Sayori (赞：1)

### Description  
给出 $4$，$7$，$47$，$74$ 的个数，问是否有这样一个 $47$ 字符串满足要求，若存在，则输出这个字符串，否则，输出 $-1$  
### Solution  
这种题目，显然是有规律可循的。手玩一下数据，就会发现 $47$ 和 $74$ 这两者数量的差值不超过1，所以只需先构造一个4和7交替的字符串满足 $47$ 和 $74$ 的个数，在判断 $4$ 和 $7$ 的个数是否满足即可，细节见代码
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5], cnt;
bool fl = 0;
int ans[2000010];
int main(){
	for(int i = 1; i <= 4; ++i)
		scanf("%d", &a[i]);
	if(a[1] < a[3] || a[2] < a[3] || a[1] < a[4] || a[2] < a[4] || abs(a[3] - a[4]) > 1){
		//若4 or 7的数量 < 47 or 74的数量，显然是构成不了的，还有就是 47 和 74数量之差不超过1
		puts("-1"); return 0;
	}
	int x = a[1], y = a[2], z = a[3], w = a[4];
	ans[cnt = 1] = 4; x--;
	while(z > 0 || w > 0){
		ans[++cnt] = fl == 0 ? 7 : 4;
		if(fl == 0) z--, y--;
		else w--, x--;
		fl ^= 1;
	}//构造以4为首项的47字符串
	if(x < 0 || y < 0 || z < 0 || w < 0){
		x = a[1], y = a[2], z = a[3], w = a[4];
		ans[cnt = 1] = 7; y--; fl = 1;
		while(z > 0 || w > 0){
			ans[++cnt] = fl == 0 ? 7 : 4;
			if(fl == 0) z--, y--;
			else w--, x--;
			fl ^= 1;
		}//构造以7为首项的74字符串
		if(x < 0 || y < 0){puts("-1"); return 0;}//两者都满足不了，输出-1
		printf("7");
		for(int i = 1; i <= x; ++i) printf("4");//要尽可能把4插在最前面
		if(ans[cnt] == 7){
			for(int i = 2; i <= cnt; ++i) printf("%d", ans[i]);
			for(int i = 1; i <= y; ++i) printf("7");
		}else{
			for(int i = 2; i < cnt; ++i) printf("%d", ans[i]);
			for(int i = 1; i <= y; ++i) printf("7"); printf("4"); 
		}
	}else{
		for(int i = 1; i <= x + 1; ++i) printf("4");//同理
		if(ans[cnt] == 7){
			for(int i = 2; i <= cnt; ++i) printf("%d", ans[i]);
			for(int i = 1; i <= y; ++i) printf("7");
		}else{
			for(int i = 2; i < cnt; ++i) printf("%d", ans[i]);
			for(int i = 1; i <= y; ++i) printf("7"); printf("4"); 
		}
	}
}
```


---

## 作者：wyc0607 (赞：0)

### 题意简述：
给你四个正整数 $a$，$b$，$c$，$d$。让你给出一个含有 $a$个 4，$b$ 个 7，$c$ 个 47，$d$ 个 74 的字符串。

### 思路：
搜索，但爆搜肯定会炸。考虑优化。

1. 有 $a$ 个 4，$b$ 个 7。则在最极端的情况下，含有的 47，74 的总和为 $a+b$。故当 $c+d > a+b$ 时，无法求解。

2. 当 $ \left|{c-d}\right| \ge 2$ 时，无解（可自己找几个例子）。

接着再枚举即可。

---

## 作者：lin_A_chu_K_fan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF145B)
# 题意
给出一个字符串中 $4$ 的个数 $a_1$，$7$ 的个数 $a_2$，$47$ 的个数 $a_3$，$74$ 的个数 $a_4$，请你给出一个满足这样的条件的字符串，如果没有输出 `-1`。
# 思路
首先可以发现，$a1+a2$ 就等于答案字符串的长度。所以如果 $2 \times ( a3 + a4 ) > a1+a2$，一定不成立，$|a1-a2|>1$ 也不成立，否则一定有答案。那么判断完了暴力枚举就行了。

为了维护社区环境（实际上是懒），代码就不放了。求关~

---

## 作者：_zhaosihan_qwq_ (赞：0)

# 题解：CF145B Lucky Number 2
## 题目翻译：
要求输出一个只含有 $4$ 和 $7$ 的字符串满足：只有 $a1$ 个 $4$，$a2$ 个 $7$，$a3$ 个 $47$，$a4$ 个 $74$，不可能则输出 $-1$。
## 思路：
看似简单的一道题，实际可不简单，我们可以看出，$4$ 的个数与 $7$ 的个数的和是字符串的长度，当 $47$ 和 $74$ 的个数的两倍大于 $4$ 的个数与 $7$ 的个数的和时，肯定是不成立的，当 $47$ 和 $74$ 的个数的差大于 $1$ 时，也不成立，其余情况都成立，那么只要暴力枚举所有情况就行了。

---


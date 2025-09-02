# North North West

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2014autumn/tasks/icpc2014autumn_a



# 题解

## 作者：Nygglatho (赞：1)

首先，我们考虑一下怎么加上分数以及减去分数。

设 $s$ 中出现 `north` 以及 `west` 的总数为 $n$，那么分母需要是 $2^{n-1}$ 才行。因为 $2^{n-1}$ 是 $2^0, 2^1, \cdots$ 的倍数，所以，以 $2^0, 2^1, \cdots$ 作分母的数**可以**化为以 $2^{n - 1}$ 作分母的数（第一个分母乘以 $2^n$，第二个分母乘以 $2^{n - 1}$，以此类推）。

这样，从右往左读取的第一段其分子也需要乘以 $2^n$，第二段也要乘以 $2^{n - 1}$，以此类推，和原来加上或减去的分数相等。最后再约分一下就行。注意如果分母约分后变成了 $1$，那么只需要输出分子。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;

int gcd(int x, int y) {return y == 0 ? x : gcd(y, x % y);}
string str;
int fz, fm, t;
int pw = 1, q, ans;
//fz, fm 代表约分后的分子与分母，t 是每次遍历时的值
//ans 是约分前的分子，pw 是约分前的分母

int main() {
	for(; ;) {
		
		pw = 1;
		
		ans = 0;
		cin >> str;
		if (str == "#") return 0;
		
		for (t = str.size() - 1; t >= 0; ) {
			if (str[t] == 'h') ans = max(ans * 2 - 90, 0), t -= 5;
			else ans = max(ans * 2 + 90, 0), t -= 4;
			pw *= 2;
		}
		
		pw /= 2;
		
		q = gcd(ans, pw);
		fz = ans / q; fm = pw / q;
		if (fm == 1) cout << fz << endl;
		else cout << fz << '/' << fm << endl;
		//约分
	}
}
```

---

## 作者：abensyl (赞：0)

原题：[AT1026 North North West](https://www.luogu.com.cn/problem/AT1026)

~~名副其实的水题！~~

## 思路

其实思路很简单，但是代码并不短，就是检验人懒不懒的！

- 不停多组输入，知道输入到 `#` 为止。

- 遍历字符串，检测 `north` 和 `west`，而检验时只要看最后一个字母就行了。

- 如果是 `north` 分母乘以二，分子等于分子乘以 $2$ 减 $90$。

- 如果是 `west` 分母也以二，分子等于分子乘以 $2$ 加 $90$。

- 然后约分，相信这个对各位看官大佬来说就不难了。

> 但是我的约分方法与其他题解不同：

> 我们知道：分母一定是 $2^k$ 所以最大公约数一定也是 $2^n$。

>所以我们只要把分子中的 $2$ 除干净即可。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int gcd(int x, int y) {
	int ans=1; 
  while(x%2==0&&y%2==0) {
  	ans*=2,x/=2,y/=2;
  }
  return ans;
}
 
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  string s;
  int up, un, t;
  int fra, q, ans;
  while (true) {
    fra = 1;
    ans = 0;
    cin >> s;
    if (s.size() == 1) return 0;
    for (t = s.size() - 1; t >= 0; t -= 4) {
      if (s[t] == 'h') ans = max(ans * 2 - 90, 0), t--;
      else ans = max(ans * 2 + 90, 0);
      fra *= 2;
    }
    fra /= 2;
    q = gcd(ans, fra);
    up = ans / q;
    un = fra / q;
    if (un == 1) cout << up << endl;
    else cout << up << '/' << un << endl;
  }
  
  return 0;
}
```

求管理员大佬给个通过行不行！

---

## 作者：AirQwQ (赞：0)

## 思路
+ 不多说按题意模拟就行。

# 坑（重点）

1. **从后到前**的顺序（因为这点我改了 $ 20 $ 分钟）。

2. $ n $ 从 $ 1 $ 开始，不是 $ 0 $ 。

3. 输出时记得特判 $ 0 $ 和分母为 $ 1 $ 的情况。

4. 记得输出最简分数。

## 实现

- 倒叙判断，不要用 ```i--```，要灵活根据是 $ north $ 或 $ west $ 改变 ```i```。 

- 面对分数时，因为分子都是 $ 2^n $ 所以分子乘以二加减九十，分母直接乘以二就行啦。（[证明在这里](https://www.luogu.com.cn/paste/s6n6ckgp)）

- 输出偷懒用 ```__gcd()``` 就好啦~。

## AcCode:

```cpp

#include<bits/stdc++.h>
using namespace std;
int main(){
    string a;
    while(1){
    	cin>>a;
    	if(a=="#") break;
    	int i=a.size()-1,cnt=1,fenz=0,fenm=1;
    	if(a[i]=='t') fenz=90,i-=4; 
    	else i-=5;
    	for(;i>=0;){
    		if(a[i]=='t'){
    			fenz=fenz*2+90;
    			fenm*=2;
    			i-=4;
    		}
    		else{
    			fenz=fenz*2-90;
    			fenm*=2;
    			i-=5;
    		}
    	}
    	if(fenm==0)
    		cout<<fenz<<endl;
    	else if(abs(fenm/__gcd(fenz,fenm))==1)
    		cout<<abs(fenz/__gcd(fenz,fenm))<<endl;
    	else 
    		cout<<abs(fenz/__gcd(fenz,fenm))<<'/'<<abs(fenm/__gcd(fenz,fenm))<<endl;
    }
    return 0;
}
```



---


# Barnicle

## 题目描述

Barney is standing in a bar and starring at a pretty girl. He wants to shoot her with his heart arrow but he needs to know the distance between him and the girl to make his shot accurate.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF697B/5aebaf3f991f80d87e0ec849d0a3847086ffdfb5.png)Barney asked the bar tender Carl about this distance value, but Carl was so busy talking to the customers so he wrote the distance value (it's a real number) on a napkin. The problem is that he wrote it in scientific notation. The scientific notation of some real number $ x $ is the notation of form $ AeB $ , where $ A $ is a real number and $ B $ is an integer and $ x=A×10^{B} $ is true. In our case $ A $ is between $ 0 $ and $ 9 $ and $ B $ is non-negative.

Barney doesn't know anything about scientific notation (as well as anything scientific at all). So he asked you to tell him the distance value in usual decimal representation with minimal number of digits after the decimal point (and no decimal point if it is an integer). See the output format for better understanding.

## 样例 #1

### 输入

```
8.549e2
```

### 输出

```
854.9
```

## 样例 #2

### 输入

```
8.549e3
```

### 输出

```
8549
```

## 样例 #3

### 输入

```
0.33e0
```

### 输出

```
0.33
```

# 题解

## 作者：Miller2019 (赞：8)

题意：输入一个科学计数法，求它的原本形式。

开始我尝试直接用 $\red{STL}$ $\red{string}$ 模拟，结果 [$\blue{TLE}$](https://www.luogu.com.cn/record/35439940) 了，这里不多赘述。

[$\color{black} Code(cpp)$](https://www.luogu.com.cn/paste/x2i8ofkj)

然后我发现了这道题可以使用 $scanf$ 的高级用法，变直接通过此题。

$Code(cpp):$

```cpp
#include<cstdio>
int i,digit,k;
char d[101];
int main()
{
    scanf("%d.",&i);
    scanf("%[^e]%ne%d",d,&digit,&k);
    //i 为整数部分 ，d 为小数部分 ，digit 为字符 'e' 之前的位数 ，k 为 科学计数法(即为'e'之后的数)。
    //%[^...]表示读到 '...' 时结束。
    //%n 表示之前读到的个数。
    if(digit==1&&d[0]=='0'&&!k)     //判断特殊情况。
    {
        printf("%d",i);
    }
    else if(k>=digit)	//如果科学计数法大于前面的位数，则需要在后面添 0 。
    {
        printf("%d%s%.*d",i,d,k-digit,0);   //先输出整数部分和小数部分，再输出 k-digit 个 0 。
    }
    else
    {
        printf("%d%.*s.%s",i,k,d,d+k);  //输出整数部分和 k 位小数部分，然后输出 '.'，再输出剩下的小数部分。
    }
    return 0;
}
```
[$\color{green}\text{亲测：最优解 497ms/3.54MB	最优解}$](https://www.luogu.com.cn/record/35495231)

蒟蒻的第 15 篇题解。

---

## 作者：zsh_haha (赞：1)

### 题目解析

这题的大概意思就是给定形如 $AeB$ 的科学计数法表示的数字，求出原数。

### 解题思路

一开始我想利用 C++ `double` 数据类型的特性水过。

就像这样：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	double a;
	cin>>a;
	cout<<a;
    return 0;
}
```

结果 WA 掉了，因为 `double` 类型下数字太大还是会使用科学计数法。

---

以下正解：

我们知道 $AeB=A\times 10^B$，就是把 $A$ 的小数点右移 $B$ 位。

我们可以分两部分来讲：

> 一，$e$ 前为整数
> 
> 由于这里没有小数点，所以我们可以直接先输出 $A$ 然后输出 $B$ 个 $0$，相当于小数点右移然后补 $0$。

> 二，$e$ 前为小数
> 
> 这里我们可以把 $A$ 中的小数右移 $B$ 位，然后输出。
> 
> 我们可以分成三部分来右移小数点：
>
> 1. 原来整数部分不动；
> 
> 2. 把小数点后的 $B$ 位小数移到整数部分；
> 
> 3. 剩下的小数正常输出。
> 
> 具体看代码。

### AC 代码

代码很长，请耐心查看。

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[100000],b[100000];
int main(){
	cin>>a;
	int l=strlen(a),l1=-1,l2=-1;
	int zhi=0;
	for(int i=0;i<l;i++){
		if(l2!=-1){
			zhi=zhi*10+a[i]-'0';//记录指数 
		}
		if(a[i]=='.'){
			l1=i;//记录小数点位置 
		}
		if(a[i]=='e'){
			l2=i;//记录 e 的位置 
		}
	}
	if(l1==-1){//没有小数点，e 前是整数的情况 
		for(int i=0;i<l2;i++){
			cout<<a[i];
		}
		for(int i=1;i<=zhi;i++){
			cout<<0;
		}
	}else{//重点，解决 e 前是小数的情况 
		int cnt=0;
		bool flag=true;
		for(int i=0;i<l1;i++){//首先把没有涉及到小数点右移的整数部分记录下来 
			if(a[i]!='0'){//解决前导 0 
				flag=false;
				b[++cnt]=a[i];//由于还要解决小数后缀 0 的情况，记录下来，先不输出 
			}else{
				if(!flag){
					b[++cnt]=a[i];
				}
			}
		}
		int now=l1+1;//记录当前下标 
		while(zhi--){//把小数点后 B 位小数变成整数 
			if(now>=l2){
				if(flag){//注意这里也要处理前导 0 
					now++;//别忘了更新下标 
					continue;
				}
				b[++cnt]='0';
			}else{
				if(flag&&a[now]=='0'){//同上 
					now++;
					continue;
				}
				flag=false;
				b[++cnt]=a[now];
			}
			now++;
		}
		if(flag){
			b[++cnt]='0';//如果整数部分全是前导 0 需要留一个 0 
		}
		for(int i=now;i<l2;i++){//如果后面还有小数就记录 
			if(i==now){
				b[++cnt]='.';//别忘了小数点 
			}
			b[++cnt]=a[i];
		}
		flag=false;
		for(int i=1;i<=cnt;i++){//注意这里很重要
			if(b[i]=='.'){//只有有小数部分是才能处理后缀 0，整数部分就不能去后缀 0 
				flag=true;
				break;
			}
		}
		for(int i=cnt;i>=0;i--){//处理小数后缀 0 
			if(flag&&b[i]=='0'){
				cnt--;
			}else{
				if(b[i]=='.'){
					cnt--;
				}
				break;
			}
		}
		for(int i=1;i<=cnt;i++){//输出 完结撒花 
			cout<<b[i];
		}
	}
    return 0;
}
```

挑战最优解：此代码实测 $15ms/172KB$

---

## 作者：wenlebo (赞：0)

读入完全可使用字符串输入流，其余的就是各种判定，按题意模拟将小数点右移。下面是要注意的。

- 不能直接读入小数，因为它可能很长。

- 有可能没有小数点！

- 结尾的 $0$ 要统统删掉。

- 不能有过多前导零。

- 记得在最后补上一些多余的零。

- 等等等等。

- 要注意的是我有些部分的代码经过了大量修改可能出现重复现象，注意辨别！


上代码慢慢查吧，其他内容我补充在代码注释：


```
#include <bits/stdc++.h>
using namespace std;
string a,d;
int b;
string c;
int main(){
	cin>>c;
	c[c.find('e')]=' '; //预处理，在两个数之间加入空格（方便读入）。
	if(c.find('.')==-1){   //可能没有小数点。
		istringstream is(c); //开启字符串流读入。
		is>>a>>b;
		d="";
	}else{  
		c[c.find('.')]=' ';   //有小数点则分开读入分子分母。
		istringstream is(c);
		is>>a>>d>>b;
	}
	if(a=="0"&&d=="0"){  
		cout<<0;
		return 0;
	}
	b+=a.size();  
	d=a+d;  //把它们连起来，更方便。
	for(int w=d.size()-1;w>=0;w--){  //去除前导零。
		if(d[w]!='0'){   
			break;
		}
		d.erase(w);
	}
	bool zero=1;
	for(int h=0;h<d.size();h++){ //输出前序部分。
		if(h==b){
			if(zero){
				cout<<0;
			}
			cout<<".";
			zero=0;
		}
		if(d[h]=='0'&&zero){
			continue;
		}
		zero=0;
		cout<<d[h];
	}
	for(int h=d.size();h<b;h++){//后头加零。
		if(zero){
			break;
		}
		cout<<"0";
	}
	if(zero)cout<<0;
    return 0;
}
```


---

## 作者：Uuuuuur_ (赞：0)

题意十分地简单，这里提供一个比较简单的做法。

首先，我们将一个**足够大**的字符数组 $ans$，每一位初始化为 ```'0'```。


然后将读入的 $e$ 前面的字符串加进来。

每一次右移，就是将小数点所在位和下一位交换。

然后从后往前找到第一个不是 ```'0'``` 的，这就是所要输出的最后一位（当然如果这位是小数点还要再减一位）。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int b, pos, len, en = 100004;;
char ans[100005];
int main() {
    char tmp;
    for (int i = 0; i < 100005; i++) ans[i] = '0';
    while (cin >> tmp) {
        if (tmp == 'e') break;
        if (tmp == '.') pos = len;
        ans[len++] = tmp;
    }
    cin >> b;
    while (b--) {
        swap(ans[pos], ans[pos + 1]);
        pos++;
    }
    while (ans[en] == '0') en--;
    if (ans[en] == '.') en--;
    for (int i = 0; i <= en; i++) cout << ans[i];
    return 0;
}
```


---

## 作者：LOVE_Ynoi (赞：0)

# CF697B 题解
题目大意：给出一个用科学计数法表示的数，把他转成原本形态。  
思路非常清晰，就是将小数点向右移位，若移动的位数超过原数的位数，就往后添零。  

这里介绍一下关于 ``string `` 的函数,  
下面代码使用到的：  
1. ``int find(char x)`` ： 在字符串中找到字符 $x$ 的位置(从 0 开始)。
2. ``string substr(int pos)`` :  从 $pos$ (从 0 开始)开始截取字符串。  
3. ``string substr(int pos,int len)`` :  从 $pos$ 处开始截取长度为 $len$ 的字符串。  
4. ``int stoi(string x)`` ：将字符串 $x$ 转变为数字。  
5. ``void erase(iterator pos)`` ： 将 $pos$ 处的字符删去(传入迭代器)。  
6. ``iterator begin()`` ：  返回开头处的迭代器。
7. ``int size()`` ： 返回字符串的长度。
8. ``void insert(int pos,string x)`` ： 在 $pos$ 处插入字符串 $x$。  
9. ``void append(int x,char c)`` ： 在字符串后面插入 $x$ 个字符 $c$ 。 

代码：
```c++
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string x;
    cin >> x;
    if (x.substr(1) == ".0e0")
    //若输入数据为1.0e0,按照下面的，我们的程序会输出1.0 而非 1
    //需要特判
    {
        cout << x[0] << endl;
        return 0;
    }
    //找到e的位置
    int pos = x.find('e');
    //前面
    string f = x.substr(0, pos);
    //后面
    string d = x.substr(pos + 1);
    //右移位数
    int n = stoi(d);
    //删除 '.' （'.'必然在第二个字符上）
    f.erase(1 + f.begin());
    //加点
    if (f.size() - 1 > n)
        f.insert(1 + n, ".");
     //添零
    else
        f.append(n - f.size() + 1, '0');
    cout << f;
    return 0;
}
```

---

## 作者：Trilliverse (赞：0)

# 小数点右移!!

---
## 思路：
把原数拆成**整数**部分和**小数**部分 然后这题**细节**比较多 (详见代码)  ~~我太难了~~

## Code：
```
#include<bits/stdc++.h>
using namespace std;

int zheng[5],xiao[105],vis[105];//整数位，小数位
int main() {
  string s;
  cin >> s;
  int len = s.length();
  bool find = false; 
  int cnt = 0;
  string num = "";
  for(int i=0;i<len;i++) {
    if(s[i] == '.') find = true;
    if(isdigit(s[i])) {
      if(!find) zheng[i] = s[i] - '0';
      else xiao[cnt++] = s[i] - '0';
    }
    if(s[i] == 'e') {
      for(int j=i+1;j<len;j++) {
        num += s[j];
      }
      break;
    }
  }
  
  int mi = stoi(num);//幂次
  cout << zheng[0];
  
  //细节 判断要不要输出多余的0或小数点.
  if(cnt == 1 && xiao[0] == 0 && mi == 0) return 0;
  
  for(int i=0;i<mi;i++) {
    cout << xiao[i];
    vis[i] = 1;
  }

  if(mi < cnt) cout << ".";//cnt表示小数的位数
  for(int i=0;i<cnt;i++) {
    if(vis[i] == 0) cout << xiao[i];
    else continue;
  }
  
  return 0;
}
```


---

## 作者：euix (赞：0)

## **题意** :

就是输出一个用科学计数法表示的数的原本形态


## **思路** ：


- 首先 我们把它分成 整数部分 分数部分 和 移动的位数部分

- 接着 我们判断 是否需要往后加0 还是 不需要	


## **提醒** ：

**有一种特殊情况**

**例如输入1.0e0**

**那么我们需要输出1**

**没有任何多余**


# 上代码吧



```cpp
#include <iostream>
using namespace std;

string s;

int main() {
	cin >> s;
	
	if (s.substr(1) == ".0e0") {
		cout << s[0];
		return 0;
	}
	
	int n = s.size(), i = 0, x, y;
	
	while (s[i] != '.') {
		i++;
	}
	x = i; i++; //0 ~ x - 1 整数部分 x为小数点 
	
	while (s[i] != 'e') {
		i++;
	}
	y = i; i++; //x + 1 ~ y - 1小数部分 y为e 
	
	int k = 0;
	for (; i < n; ++i) {
		k = k * 10 + s[i] - '0';
	} //计算需要乘10的几次方 
	
	
	for (i = 0; i < x; ++i) {
		cout << s[i];
	}
	
	if (x + k < y - 1) { //不需要加0
		for (i = x + 1; i <= x + k; ++i) {
			cout << s[i];
		}
		cout << '.';
		for (i = x + k + 1; i < y; ++i) {
			cout << s[i];
		}
	}
	else { //需要加0
		for (i = x + 1; i < y; ++i) {
			cout << s[i];
		}
		for (i = 1; i <= x + k - y + 1; ++i) {
			cout << 0;	
		}
	}
}
```


---

## 作者：Abeeel51 (赞：0)

给定科学计数法，求原数。

重点是：找科学计数法的小数点。

确定整数部分和小数部分之后，将小数点右移，整数和小数位就都变化了。

这题有个 $1.0e0$ 数据，一定要特判！！！

推个数：

$1.54e10$

那么找到 $1.54e10$ 的小数点在 $1$ 和 $5$ 之间。之后找到 $e$ 在 $4$ 和 $1$ 之间，所以也就确定小数点往后移动 $10$ 位，最终就是 $154000000$。

详见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    string s;
    getline(cin,s);//整行输入
    if(s[1]=='.'&&s[2]=='0'&&s[3]=='e'&&s[4]=='0'){//特判！！！
        cout<<s[0];
        return 0;
    }
    int dotpos=0;
    int epos=0;
    for(;s[dotpos]!='.';dotpos++){
        continue;
    }
    epos=dotpos+1;
    for(;s[epos]!='e';epos++){
        continue;
    }
    int cifang=0;
    for(int i=epos+1;i<s.size();i++){
        cifang*=10;
        cifang+=s[i]-'0';
    }
    for(int i=0;i<dotpos;i++){
        cout<<s[i];
    }
    if(dotpos+cifang<epos-1){
        for(int i=dotpos+1;i<=dotpos+cifang;i++){
            cout<<s[i];
        }
        cout<<".";
        for(int i=dotpos+cifang+1;i<epos;i++){
            cout<<s[i];
        }
    }else{
        for(int i=dotpos+1;i<epos;i++){
            cout<<s[i];
        }
        for(int i=dotpos+cifang-epos;i>=0;i--){
            cout<<"0";
        }
    }
    return 0;
}
```


---


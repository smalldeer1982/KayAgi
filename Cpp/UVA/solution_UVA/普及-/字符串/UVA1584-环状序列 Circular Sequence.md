# 环状序列 Circular Sequence

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4459

[PDF](https://uva.onlinejudge.org/external/15/p1584.pdf)

# 题解

## 作者：sss7020 (赞：11)

代码比较简洁。说一个东西：

# 我谷难道没有人会用黑科技（也不算黑）

用sort()排字符串数组（string数组，c++）就是按字典序排的（系统已重载运算符），所以一个sort就搞定了！

老规矩：先上代码，再说废话：
```
#include<iostream>
#include<string>
#include<algorithm>
//sort必备
using namespace std;
int main(){
    string s;
    int kase,k;
    cin>>kase;
    while(kase--){//循环开始了
        cin>>s;//输入字符串
        string st[105];
        //为节省空间，系统将string类默认为空串
        for(k=0;k<s.length();k++){
        	//k是代表从哪个字符开始读
            for(int i=k;i<k+s.length()/*循环s.lenth()次*/;i++){
                st[k]+=s[i%s.length()];
                //字符串往后填几个字符串
                //+运算符的用法：
                //看我题解：
                //https://www.luogu.org/blog/winnerking1412/solution-uva455
            }
        }
        sort(st,st+s.length());
        //排序
        cout<<st[0]<<endl;//输出第一个字符串
    }
    return 0;
}
```

废话来了！

方法：用%模拟环形

不具体是不是？听我慢慢跟你说。

要是用%的话，那么$s.lenth()$位就是第0位

（$s.lenth()$%$s.lenth()==0$）

懂了吧（没懂跟我私信）

具体方法：

首先，用k作从哪一位开始数形成的环形，用%模拟环形，并将字符一个一个存入数组中对应字符串中，最后将数组排序，输出第一个（也就是经排序后最小的（已经改变数组）），然后再输入一个字符串，直到EOF。


~~听懂了就好，没听懂也可以跟我私信~~

---

## 作者：梦里调音 (赞：6)

# 经典的 _字符串模拟题_ 

利用循环枚举+判断出各种可能即可。

记得用substr哟~~

~~短小精悍的~~代码如下：



```cpp
#include <iostream>
#include <string>
using namespace std;
int main(){
	int i,j,k,m,n;
	string s;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>s;
		string ans=s;
		for(j=0;j<s.length();j++){
			string t;
			t=s.substr(j,s.length()-j)+s.substr(0,j);//这是重点
			if(t<ans)ans=t;
		}
		cout<<ans<<endl;
	}
} 
```

---

## 作者：Zlc晨鑫 (赞：3)

首先，我觉得题意翻译比较粗略，我再补充几点，希望能帮助到大家。

1.注意有T组数据，所以要这样写：
```cpp
int T;
scanf("%d", &T);
while (T--)
{

}

```

2.关于数据范围的问题，题意翻译中似乎没有提到，但PDF里面有：“Each sequence has length at least 2 and at most 100.”。也就是说字符串的长度最少为2，最大为100。 

大家如果还有什么疑惑的话可以去看看PDF，虽然是英文，不过找找数据范围什么的还是不难的；也希望洛谷的题意翻译以后能加上数据范围之类的信息。不过，其实只要用string就可以避免字符串长度的问题。  

然后就是模拟环状，这里用%号来模拟环状，可以用其实位置q加上当前下标i，然后%长度len。这样就能保证下标的范围在0 ~ len - 1之间。  

```cpp
str[(q + i) % len];
```

接下来，可以枚举每一个其实位置，然后对其进行判断，如果字典序比之前的小，则更新起始位置。输出也是用%号实现。  

再讲讲判断函数怎么写吧。  

首先， 我们模拟环状，然后依次判断当前的字符串字符与上一个字符串的每一个字符。如果相等就continue;，小于就return true;，大于就return false。

下面是这个函数的实现：

```cpp
// old是上一个字符串的首下标，young是当前字符串的首下标。
bool cmp(int old, int young)
{
    int len = str.size();
    for (int i = 0; i < len; i++)   
        if (str[(i + old) % len] == str[(i + young) % len]) continue;
        else if (str[(i + old) % len] > str[(i + young) % len]) return true;
        else if (str[(i + old) % len] < str[(i + young) % len]) return false;
    // 如果相等则不需要交换，return false;。
    return false;
}
```

其实上面的函数判断部分还可以简化，大家自己想一想怎么做。
下面给出AC代码：

```cpp
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

// 用string可以避免字符串长度的问题
string str;

// 比较两个字符串的字典序
bool cmp(int old, int young)
{
    int len = str.size();
    for (int i = 0; i < len; i++)   
        if (str[(i + old) % len] == str[(i + young) % len]) continue;
        else if (str[(i + old) % len] > str[(i + young) % len]) return true;
        else if (str[(i + old) % len] < str[(i + young) % len]) return false;
    return false;
}

int main(void)
{
	// 有多组数据
    int T;
    scanf("%d", &T);
    while (T--)
    {
        cin >> str;
        // 先假设0为ans
        int ans = 0, len = str.size();
        // 从1开始比较
        for (int i = 1; i < len; i++)
            if (cmp(ans, i)) ans = i;
        // 用%号模拟环状并输出
        for (int i = 0; i < len; i++)
            printf("%c", str[(i + ans) % len]);
        puts("");
    }
    return 0;
}
```

---

## 作者：mnesia (赞：2)

这题我的思路比较简单，就是传统的“打擂台”：先将一个起始位置（我设的就是 0）设为“擂主”，然后逐个位置作为起始位置为“攻擂者”，通过一个函数以逐个字符比较的方式进行字典序排序，字典序小的成为新的“擂主”。

在函数部分，我通过一个 `for` 循环实现，如果起始位置经过相同的移位后所在位置的字符相等，移位就 +1，直到比较出某位置的字符大小或判断出两字符串完全相等位置。

具体代码：
```cpp
#include<iostream>
#include<string.h>
using namespace std;
const int maxn = 110;

int n;
char str[maxn];
int len;
int ans;
bool cmp(const char *str, int p, int q)
{
	for(int i = 0;i < len;i++)
	{
		if(str[(p + i) % len] != str[(q + i) % len])//起始位置不同，移位相同，对应位置上的字符串比较
			return (str[(p + i) % len] < str[(q + i) % len]);//不同则返回该位置比较的结果，若为 true 则“攻擂成功”，false 则“守擂成功”
	}
	return false;//如果没有比对出结果，那么说明两个起始位置开始的字符串完全相同，此时返回 false，对应到原函数中就是 ans 的值不发生变化，即起始位置不发生变化
}
int main()
{
//	freopen("UVA1584.in", "r", stdin);
	cin >> n;
	for(int a = 1;a <= n;a++)
	{
		ans = 0;
		cin >> str;
		len = strlen(str);
		for(int i = 1;i < len;i++)
		{
			if(cmp(str, i, ans))
			{
				ans = i;
			}
		}
		for(int i = 0;i < len;i++)
		{
			cout << str[(ans + i) % len];
		}
		cout << endl;
	}
	return 0;
}
```


---

## 作者：Dimly_dust (赞：1)

                          环状序列
- 长度为n的环状串有n种表示方法，分别为从某个位置开始顺时针得到，在这些排列中字典顺序最小的称“最小表示”。

-  如CTCC的最小表示为CCCT，CGAGTCAGCT的最小表示为AGCTCGAGTC。

-  提示：对于两个字符串，从第一的字符开始比较，当某一个位置的字符不同时，该位置字符较小的串，字典序小，如果一个字符串没有更多的字符，        但是另一个字符串还没结束，则较短的字符串的字典序较小。



   实现：
   ```cpp
#include<bits/stdc++.h>
#define MAX 101
int less(char *s, int p, int q)// 比较两个 序列的字典序
	{
		int n = strlen(s);
		for(int i = 0; i < n; i++ ){
			if(s[(p+i)%n] != s[(q+i)%n])//意味着元素相同时候继续 直到有不同的元素为止
				return s[(p+i)%n] < s[(q+i)%n];//不同时直接返回 大小关系
			}
			
		return 0;//到这一步 说明这两个序列 元素一样
	} 
	
int main()
	{
		char s[MAX];
		scanf("%s",&s);
		int n = strlen(s);
		int ans = 0;
		
		for(int i = 1; i < n; i++ ){
			if(less(s, i, ans) == 1)
				ans = i;//如果 以第i个位置开始的序列的 字典序 小于从ans位置开始的字典序
		}                       //那么 更新 ans 位置为 i
		
		for(int i = 0; i < n; i++ ){
			printf("%c",s[(ans+i)%n]);  //  (ans+n-1)%n <-> ans-1(ans前一个) || n-1(ans = 0时) 
		}
				
		return 0;
	}

```



- 思路 : 从输入的第一个字符位置开始(记为ans = 0)为一个序列, 然后记从 第二个字符开始为一个序列，每个序列的第一个元素开始按照字典序比较，直到出现第一个不同的元素为止， 如果 新的序列 字典序小于 ans（初始为0）开始的字典序,那么 更新 ans为 当前序列的 初始位置，依次进行 直到 所有元素比较完。 

---

## 作者：AC基德 (赞：1)

# 来一波C++代码

### 分析：本题出现了一个新概念：字典序

  所谓字典序，就是字符串在字典中的顺序。一般的，对于两个字符串，从第一个两个字符串，从第一个字符开始比较，当某一个位置的字符不同时，该字符较小的串，字典序较小（例如，abc比bcd小）；
###   学会了字典序的概念之后，本题就不难了。

## 思路：
就像“求n个元素的最小值”一样，用变量ans表示目前为止，字典序最小串中的起始位置，然后不断更新ans。

#### 下面是部分代码：


```c

//环状s的表示法p是比表示q的字典序小

int less(const char* s,int p,int q)
{
	int n=strlen(s);
	for(int i = 0;i < n;i++)
	{
		if(s[(p+i)%n] != s[(q+i)%n]);
			return s[(p+i)%n] < s[(q+i)%n];
	}
	return 0;//相等 
} 

```


#### 下面是主函数：

```c
	while(T--) {
		scanf("%s", s);
		int ans = 0;
		int n = strlen(s);
		for(int i = 1;i < n;i++)
		{
			if(less(s, i, ans))
				ans = i;
		}
		for(int i = 0;i < n;i++)
			putchar(s[(i+ans)%n]);
		putchar('\n');
	}
```
//完结撒花


### //本蒟蒻60分钟的题解，大佬勿喷

---

## 作者：fjy666 (赞：0)

### 0x01 思路
我们可以枚举起点 $i$ ，再判断它开头构成的子串能否构成字典序**最小**的子序列。  
时间复杂度为：$\Theta(T \times n^2)$  
- $T:$测试数据组数
- $n:$字符串长度

知识点：`strcmp(str1,str2)`  
它用来比较两个字符串字典序的大小，
- $str1 = str2$ -> $return\ 0$
- $str1 < str2$ -> $return\ <1$
- $str1 > str2$ -> $return\ >1$

剩下的内容，只要根据题意模拟即可。

------------
### 0x02 代码
```cpp
#include <cstdio>
#include <cstring>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define fr(i_,j_,k_) for(int i_=j_;i_>=k_;--i_)
#define It(type_) type_::iterator
#define rg register
#define rtn return
#define il inline

typedef long long ll;
const int kMaxn = 111;
char str[kMaxn],to[kMaxn],tmp[kMaxn];

void GetStr(const char * __restrict_source,char* destination,int st_pos)
{
#define str __restrict_source
#define to destination
#define st st_pos
	int l = strlen(str);
	fo(i,1,l)
	{
		*to=str[st];
		++to;
		st=(st+1)%l;
	}
	*to='\0';
#undef str
#undef to
#undef st
}
int main()
{
	int TestCase;
	scanf("%d",&TestCase);
	while(TestCase--)
	{
		scanf("%s",str);
		GetStr(str,to,0);
		int L = strlen(str);
		fo(i,1,L-1)
		{
			GetStr(str,tmp,i);
			if(strcmp(tmp,to)<0)
				memcpy(to,tmp,sizeof(to));
		}
		puts(to);
	} 
    rtn 0;
}
```
**注意：`*to='\0';`必须写，不写会导致数组越界！**

---

## 作者：张良敏 (赞：0)

有两种方法，一种使用TreeSet，他会自动从小到大排序，一般有默认的排序规则，如果是数字呢，就按小到大，如果是字符串呢就按ascll码比较，就好像ab比ac小，怎么比的呢，就是先比较第一位，如果相同再比较第二位，那么b的ascll码比c小，那么ab就比ac小了。第二种呢，其实原理都是一样，第一种是jdk给我们实现的，第二种是我自己写的，做这种题呢，就不要想着做出来就行了，原理还是要知道的，不然就没意义了，不多说了，直接贴两种方法的


```java
import java.util.Scanner;

public class F1 {
    public static void main(String[] args) {
        /**
         * 方法一
         */
/*        Scanner cin = new Scanner(System.in);
        int count = Integer.valueOf(cin.nextLine());
        for (int j = 0; j < count; j++) {
            TreeSet treeSet = new TreeSet();
            int flag = 0;
            String line = cin.nextLine();
            String ss = line;
            for (int i = 0; i < line.length(); i++) {
                String s = line.substring(i) + line.substring(0, i);
                treeSet.add(s);
            }
            System.out.println(treeSet.first());
        }*/
        /**
         * 方法二
         *想了好半天，结果还是想到了给字符串排序，但是字符串排序还是想了好半天，怎么排呢，就是一位一位的排，
         * 如果排到相同的就继续比较，不相同的呢最小的那个就是我想要的最小字典序的字符串
         */
        Scanner cin = new Scanner(System.in);
        int count = Integer.valueOf(cin.nextLine());
        for (int j = 0; j < count; j++) {
            String line = cin.nextLine();
            String ss = line;
            for (int i = 0; i < line.length(); i++) {
                String s=line.substring(i) + line.substring(0, i);
                for (int k = 0; k <s.length() ; k++) {
                    char c = s.charAt(k);
                    char c1 = ss.charAt(k);
                    if (c<c1){
                        ss=s;
                        //继续比较
                    }else if (c==c1){
                        continue;
                    }else {
                        break;
                    }
                }
            }
            System.out.println(ss);
        }
    }
}
 

```



---

## 作者：PC_DOS (赞：0)

这是一道字符串模拟题，为了处理方便，我们可以记录输入字符串的长度iLength，之后将输入的字符串复制一份并加到它的末尾，这样就可以直接从输入串的头部到尾部走一遍，以目前读到的字符为基准取iLength个字符，并和现有的最小串比较即可。

代码:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sInput, sCurrent, sMin; //sInput-输入的字符串；sCurrent-目前读取到的用于比较的字符串；sMin-字典序最小的字符串
	int nCount, i, j, iLength; //nCount-查询个数；i、j-循环计数器；iLength-存放输入字符串的原始长度
	cin >> nCount; //读入询问个数
	for (i = 1; i <= nCount; ++i){ //接受询问
		cin >> sInput; //读入字符串
		iLength = sInput.length(); //记录原始长度
		sMin = sInput; //假设原串字典序最小
		sInput += sInput; //复制一份加到末尾
		for (j = 1; j < iLength; ++j){ //从输入串的头部到尾部走一遍
			sCurrent = sInput.substr(j, iLength); //以目前读到的字符为基准取iLength个字符
			if (sCurrent < sMin){ //和sMin比较，如果目前抽取的字符串字典序更小
				sMin = sCurrent; //记录
			}
		}
		cout << sMin << endl; //输出最小者，勿忘换行
	}
	return 0; //结束
}
```

---


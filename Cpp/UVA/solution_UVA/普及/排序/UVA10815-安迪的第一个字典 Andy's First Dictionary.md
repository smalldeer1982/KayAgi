# 安迪的第一个字典 Andy's First Dictionary

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1756

[PDF](https://uva.onlinejudge.org/external/108/p10815.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10815/4f5c1d24c1c6cb6c76b70bd32c63daec8b95b2f4.png)

## 样例 #1

### 输入

```
Adventures in Disneyland
Two blondes were going to Disneyland when they came to a fork in the
road. The sign read: "Disneyland Left."
So they went home.```

### 输出

```
a
adventures
blondes
came
disneyland
fork
going
home
in
left
read
road
sign
so
the
they
to
two
went
were
when```

# 题解

## 作者：Morning_Glory (赞：20)

```c
//这道题其实可以用STL中的set（集合）来解决
#include <iostream>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
set<string>p;
set<string>::iterator iter;//迭代器
string s;
char ch;
int main ()
{
	while ((ch=getchar())!=EOF){//一个一个读取
		if (!isalpha(ch))continue;//如果是空格或者符号就不看
		while (isalpha(ch)){
			ch=tolower(ch);//将读到的字母转为小写
			s+=ch;//s后面加入ch
			ch=getchar();
		}
		p.insert(s);//给集合中添加元素
		s.clear();//s清空
	}
	for (iter=p.begin();iter!=p.end();iter++)
		cout<<*iter<<endl;//由于set会自动按照字典序排序，所以只要顺序输出就好了
	return 0;
}


```

---

## 作者：风浔凌 (赞：19)

~~这个貌似不是一篇纯题解~~
# 其实我只是来介绍一下一些STL操作：

## 1、set 
集合
哦....对了，set有自动**按照字典序排序**功能。。。。。 

### 声明和插入操作
```
#include <cstdio>
#include <vector>
#include <set>
using namespace std;
int main(){
        vector<int> v;
        for (int i = 0; i < 10; i++)
		{
                v.push_back(i);
                v.push_back(i);
        }
        set<int> s;
        s.insert(v.begin(), v.end());
        //因为是集合，所以重复的元素不会被重复插入
        for (set<int>::iterator it = s.begin(); it != s.end(); it++)
                printf("%d\n", *it);
        printf("\n");
        return 0;
}
```
### 删除操作 
这个一般都用的是erase()--->删除指定的元素或者删除指定部分的元素 
  和 clear()--->清除所有元素
  操作如下：
```
    set<int> s;
    s.erase(2);        
    s.clear();
```

### 查找操作
set支持upper_bound() lower_bound() find()等操作
举个例子： 
```
   set<int> s;
   set<int>::iterator it;
   it = s.find(5);    //查找键值为5的元素
   if (it != s.end())    //找到了 
   cout << *it << endl;
   
```

## 2、isalpha() 
判断字符ch是否为英文字母，若为英文字母，返回非0（小写字母为2，大写字母为1）。若不是字母，返回0。
具体用法见下 

## 3、stringstream()
输入输出转换操作
具体用法见下 

## 4、tolower()
是一种函数，功能是把字母字符转换成小写，非字母字符不做出处理。
具体用法见下 


下面是该题代码：
```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<sstream>
#include<set>
using namespace std;
set<string>aa;
string s,cur;
int main(){
    std::ios::sync_with_stdio(false);
    while(cin>>s)
    {
        for(int i=0;i<s.length();i++)
        {
            if(isalpha(s[i]))  s[i]=tolower(s[i]);
            else s[i]=' ';
        }
        stringstream ss(s);
        while(ss>>cur)  
            aa.insert(cur);
    }
    for(set<string>::iterator it=aa.begin();it!=aa.end();it++)
    {
        cout<<*it<<endl;
    }
    return 0;
}
``` 

---

## 作者：血色黄昏 (赞：6)

### 送上本题第一篇python题解~(热烈庆祝)

我的思路是将每行用空格分隔成字母，转换成小写，再用python的set去重，排序后输出。10行代码简洁明了，你值得拥有QwQ

上代码：
```python
s = set()#将s变成一个set容器
ans = 'a'#输入用的
while ans != '':#如果没读到文件结束就一直读
    ans = input()#输入一整行
    ans1 = ans.split()#按空格分割成一个含有单词的列表
    for i in ans1:#把ans1里的每项拿出来
        s.add(i.lower())#把每个单词的小写加进s
s = sorted(s)#将数据排序
for i in s:#s里的每一项拿出
    print(i)#按字典序输出并换行
```

祝大家AC了这道题~

---

## 作者：WanderingTrader (赞：3)

这题嘛，set入门题。  
### set
set是STL里的一个容器，它的主要功能是去重+排序，特别适合本题。  
例：已知有$n$个数字$a_i$，请将它们从小到大输出，相同的数字只输出一个。  
解法有很多种，可以排完序后特判，可以用map，在$a_i$很小的时候甚至可以用桶排。不过这里使用set。  
既然用到了set，首先要导入头文件
```cpp
#include <iostream>
#include <cstdio>
#include <set> //使用前别忘了带头文件 
```
然后定义一个set：
```cpp
set <int> s;//定义了一个存放整数的set:s
```
要想在set中放入数据，使用insert函数，即：
```cpp
#include <iostream>
#include <cstdio>
#include <set> //使用前别忘了带头文件 
using namespace std;
inline int read()
{
	int x=0,f=1;
	char c = getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	set <int> s;//定义了一个存放整数的set:s
	int n=read();
	for(int i = 1;i <= n;++ i) 
		s.insert(read()); //在set中插入读到的整数
	return 0;
}
```
输入完了，如何遍历整个set呢？和其他许多STL容器一样，采用迭代器：
```cpp
set <int> ::iterator it;//迭代器 
for(it = s.begin();it != s.end();++it)//基本的遍历set的方法
	printf("%d ",*it); 
printf("\n");
```
完成了。  
```cpp
#include <iostream>
#include <cstdio>
#include <set> //使用前别忘了带头文件 
using namespace std;
inline int read()
{
	int x=0,f=1;
	char c = getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	set <int> s;//定义了一个存放整数的set:s
	int n=read();
	for(int i = 1;i <= n;++ i) 
		s.insert(read()); //在set中插入读到的整数
	set <int> ::iterator it;//迭代器 
	for(it = s.begin();it != s.end();++it)//基本的遍历set的方法
		printf("%d ",*it); 
	printf("\n");
	return 0;
}
```
从上面的代码中可以看到，迭代器的本质是指针，若想访问里面的值，需要在前面加上\*号。  

set的插入复杂度大约为$O(\log n)$，和map,priority_queue都差不多。  

set的基本介绍就到这里，大家可以在实践中发现它的更多功能。  
### 本题代码
言归正传，现在来讲这道题。  
初始化：
```cpp
#include <iostream>
#include <cstdio>
#include <set>
#include <string>
using namespace std;
int main()
{
	string str;
	char ch = getchar();
	set <string> S;
	set <string> ::iterator it;
	return 0;
}
```
首先读入怎么处理，这里分类讨论：
1. ch是字母  
直接加入字符串即可。
2. ch不是字母
如果字符串的为空(长度=0)，那么就不要放入set，否则放入(字符串内凡是存在的字符必然为字母)

那么代码就很简单了：
```cpp
while(ch != EOF)
{
	if(!isalpha(ch)) 
	{
		if(str.length())
			S.insert(str);
		str.clear();
	}
	else
	{
		if(isupper(ch)) 
			ch = ch - 'A' + 'a';
		str += ch;
	}
	ch = getchar();
}
```
别忘了大小写处理。  

现在遍历整个set输出即可。  
```cpp
it = S.begin();
for(;it != S.end();++it)
	cout << *it << endl;
```
全部代码：
```cpp
#include <iostream>
#include <cstdio>
#include <set>
#include <string>
using namespace std;
int main()
{
	string str;
	char ch = getchar();
	set <string> S;
	set <string> ::iterator it;
	while(ch != EOF)
	{
		if(!isalpha(ch)) 
		{
			if(str.length())
				S.insert(str);
			str.clear();
		}
		else
		{
			if(isupper(ch)) 
				ch = ch - 'A' + 'a';
			str += ch;
		}
		ch = getchar();
	}
	it = S.begin();
	for(;it != S.end();++it)
		cout << *it << endl;
	return 0;
}
```
于是我们的AC题数又增加了1。  

这题主要就是让大家熟悉set(被《算法竞赛入门经典2》作为例题)。  

$\mathrm{The\ End.}$

---

## 作者：warzone (赞：3)

看楼下都用STL啊....蒟蒻着实不习惯，用字典树AC

新手可以看一看字典树的基本思路，搜索引擎的关键字检索经常用到字典树

（以及由它延伸出的AC自动机）
```cpp
#include<cstdio>
using namespace std;
char c='a',s[256];
struct point{
	bool b;
	point *next[26]; 
}head,*p;
inline void out(point *p,short step){
	if(p->b){
		for(short i=0;i<step;i++)putchar(s[i]);
		putchar('\n');
	}//有则输出，但仍继续往下走（还有更长单词，字典序上靠后）
	for(short i=0;i<26;i++){
		if(p->next[i]!=NULL){	//字典树往下走
			s[step]=i+'a';		//走时记录单词（step）
			out(p->next[i],step+1);
		}
	}
}
inline void down(){
	if(p->next[c]==NULL){
		p->next[c]=new point;
		p->next[c]->b=0;
		for(short i=0;i<26;i++)p->next[c]->next[i]=NULL;
	}							//下行+建树
	p=p->next[c];
}
int main(){
	head.b=0;
	for(short i=0;i<26;i++) head.next[i]=NULL;
	p=&head;
	do{
		c=getchar();
		if('A'<=c&&c<='Z'){//大写和小写分开
			c-='A';
			down();
		}
		else if('a'<=c&&c<='z'){
			c-='a';
			down();
		}
		else if(p!=&head){//一个单词读完标记
			p->b=1;
			p=&head;
		}
	}while(~c);//读完文件
	out(&head,0);
    return 0;
}

```

---

## 作者：Into_qwq (赞：2)

## 这道题目运用到的STL有$set$和$string$

首先简单介绍一下$set$

**$set$就是一个集合，其特性是自动排序和插入进去的元素不会重复**

基本用法：

$insert(x)$ 在这个集合中插入一个元素$x$

$erase(x)$ 在这个集合中删去元素$x$

$lower\_bound$和$upper\_bound$ 二分

$count(x)$ 判读$x$是否在集合中出现过

$size()$ 返回元素个数

$clear()$ 清空容器

代码中还有一个函数$isalpha(x)$，这个函数是用来判断字符$x$是否是字母(不在乎大小写)的$qwq$

代码：
```c++
#include<bits/stdc++.h>
using namespace std;
set <string> s;//定义集合
set<string>::iterator it;//迭代器
string s1,s2;
inline char change(char x){return  x < 'a'? x - 'A' + 'a' :x;}//把$x$变成小写字母
int main(){
    while(cin>>s1){
        s2.clear();//每次都要清空，很重要
        for(int i=0;i<s1.size();++i)
        	if(isalpha(s1[i])) s2+=change(s1[i]);//如果这个字符是字母，就将其加到s2的后面
        	else if(s2.size() > 0) {//如果这个字符不是字母且s2长度大于0(相当于s2已经是文中的一个单词)
            	s.insert(s2);//就把这个字符串丢到集合里
                s2.clear();//并且把s2清空
            }
        if(s2.size() > 0) s.insert(s2);//同上
    }
    for(it=s.begin();it!=s.end();++it) cout<<(*it),putchar('\n');//输出集合中的字符串
    return 0;
}
```

$\color{red}\text{THE END}$

---

## 作者：_Qer (赞：2)

提供一个无指针字典树做法

树上的每个节点存两个信息  
1. 当前节点的字符是否为一个单词的最后一个字符  
2. 当前节点的所有子节点编号

输出的时候可以用dfs遍历这棵树，当遇到了某个节点被记录为某个单词的结尾时输出

```cpp
#include <bits/stdc++.h>
using namespace std;
using namespace io;
int cnt;//节点数
struct node {
    bool ed;//是否为某单词结尾
    int son[30];//子节点编号
    //son[i]表示当前字符的下一位是(char)(i+'a')时的节点编号
} tr[50010];
void add(string &s) {//添加字符串
    int l = s.length(), tt = 0;
    for (int i = 0; i < l; ++i) {
        if (!tr[tt].son[s[i] - 'a']) {//没有这个节点，需要新建
            tr[tt].son[s[i] - 'a'] = ++cnt;
        }
        tt = tr[tt].son[s[i] - 'a'];
        if (i == l - 1) {
            tr[tt].ed = true;
        }
    }
}
char ch[3000];
void dfs(int nt, int k) {//nt为当前节点编号，k为当前字符串长度
    if (tr[nt].ed) {
        cout << ch << endl;
    }
    for (int i = 0; i < 26; ++i) {//遍历可能的下一位
        if (tr[nt].son[i]) {
            ch[k] = i + 'a';
            dfs(tr[nt].son[i], k + 1);
            ch[k] = 0;
        }
    }
}
int main() {
    char c;
    while (scanf("%c", &c) != EOF) {
        if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) {
            continue;
        }//不是字母直接跳过
        string s("");
        do {//记得要把大写字母都转换成小写
            if (c >= 'A' && c <= 'Z') {
                s += (char)(c + 'a' - 'A');
            } else if (c >= 'a' && c <= 'z') {
                s += c;
            } else {
                break;
            }
        } while (scanf("%c", &c) != EOF);
        add(s);
    }
    dfs(0, 0);
	return 0;
}
```

---

## 作者：andyli (赞：1)

楼下的代码比较乱，我来整理一下。本题没有太多的技巧，只是考验STL的用法，可以用set保存各个单词~~，还可以用输出迭代器（ostream_iterator）来输出~~。注意：输入时应把所有非字母的字符变成空格，然后利用stringstream得到各个单词。提示一下，set会自动排序，所以不用sort进行排序。代码如下（本人一贯偷懒，所以利用C++11来小小的简化了代码）：
```cpp
#include <algorithm> // 提供copy
#include <iostream>  // 提供cin, cout
#include <iterator>  // 提供ostream_iterator
#include <sstream>   // 提供stringstream
#include <string>    // 提供string
#include <cctype>    // 提供isalpha, tolower
#include <set>       // 提供set
using namespace std;

set<string> d;
int main()
{
	string s, tmp;
	while (cin >> s)
	{
		for (auto& x : s) // C++11
		{
			if (isalpha(x))
				x = tolower(x);
			else
				x = ' ';
		}
		stringstream ss(s);
		while (ss >> tmp)
			d.insert(tmp);
	}
	ostream_iterator<string> out(cout, "\n");
	copy(d.begin(), d.end(), out);
	return 0;
}
```
注：各位千万不要抄袭，否则棕名后果自负（不要复制粘贴加提交）。

---

## 作者：PC_DOS (赞：1)

这是一道字符串模拟题，但是一些小坑点还是有的。最大的坑就是分格两个单词的不一定是空格。

为了解决这个问题，我们可以采用另一种读单词的方法，即首先读入整行，之后一个字符一个字符地读过去，如果当前字符是字母，把这个字符加到当前正在读的单词中，同时设置标识符表示目前在单词中。如果当前字符不是字母但是标识符为真(即先前在单词中)，则表示读取完了一个单词，此时设置标识符为假并判断是否单词是否出现过，若没有则将其加入字典。

注意，行的末尾可能也有单词，因此在一整行处理完之后别忘了判断一下存放单词的字符串是不是空，若非空则判断是否单词是否出现过，若没有则将其加入字典。

判断单词是否出现过可以用一个从string映射到bool的map实现，如果map[string]为假则表示字符串没有出现过，每次加入一个单词都应当将这个单词符对应的键值设为真。

按照字典序排序直接使用sort()即可。

注意，题目需要输出小写。

代码:
```
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
#include <map>
using namespace std; //头文件和命名空间
string ToLower(string sOrigin){ //字符串小写函数
	if (sOrigin.length() == 0){
		return "";
	}
	string ans("");
	long i;
	for (i = 0; i <= sOrigin.length() - 1; ++i){
		if (sOrigin[i] >= 'A' && sOrigin[i] <= 'Z')
			ans += char(sOrigin[i] + ('a' - 'A'));
		else
			ans += sOrigin[i];
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	vector<string> arrWords; //存放单词的动态数组
	map<string, bool> mapWords; //标识单词是否出现过
	string sInput, sProcess; //sInput-输入的原始数据；sProcess-暂存单词
	bool IsInWord=false; //标识当前是否在单词中
	register int i; //循环计数器
	while (getline(cin,sInput)){ //循环读取
		sInput = ToLower(sInput); //转换为小写
		for (i = 0; i < sInput.length(); ++i){ //遍历字符串
			if (isalpha(sInput[i])){ //如果当前字符是字母
				IsInWord = true; //当前在单词中
				sProcess += sInput[i]; //把这个字符加到当前正在读的单词中
			}
			else if (IsInWord){ //如果当前字符不是字母但是标识符为真(即先前在单词中)
				IsInWord = false; //当前不在单词中
				if (!mapWords[sProcess]){ //判断单词有没有出现过
					mapWords[sProcess] = true; //将这个单词的键值设为真，标识出现过
					arrWords.push_back(sProcess); //单词放入数组
				}
				sProcess = ""; //清空暂存区
			}
			else{ //其他情况
				sProcess = ""; //清空暂存区
			}
		}
		if (sProcess.length() != 0 && !mapWords[sProcess]){ //一整行处理完之后别忘了判断一下存放单词的字符串是不是空，若非空则判断是否单词是否出现过
			mapWords[sProcess] = true; //将这个单词的键值设为真，标识出现过
			arrWords.push_back(sProcess); //若没有则将其加入字典
		}
		sProcess = ""; //清空暂存区
		IsInWord = false; //当前不在单词中
	}
	sort(arrWords.begin(), arrWords.end()); //按照字典序排序
	for (i = 0; i < arrWords.size(); ++i){ //输出
		cout << arrWords[i] << endl;
	}
	return 0; //结束
}
```

---

## 作者：苏打青柠水 (赞：0)

发一篇java的字典树做法。我在做的时候遇到了一个坑，找了很久才找到。那就是在输入的时候需要特殊处理一下每一行的字符串，先变成小写字母，还有处理一些非a-z的符号，刚开始的时候，我是直接利用spilt(" ")分割再处理非a-z，但是这会存在一个问题，如果是a,aa  b,aa这样的字符串的话，我们就会把a,aa当成一个单词，再处理的话就会变成aaa，但是真正的结果是a和aa两个单词.所以应该先处理非a-z，再分割。具体的细节在代码会提到。
```java

import java.util.Scanner;

public class Main {

	static Tree tree[] = new Tree[50010];  //字典树
	static int tot = 0;   //字典树的内存池的当前位置
	static String source[] = new String[50010];   //保存字符串的下标

	static class Tree {
		int next[] = new int[26];   //保持当前节点的a-z
		int number;    //单词结束标识，也是取原字符串的下标
	}

	static void insert(char[] s, int num) {   //参1：字符串，参2：单词的下标
		int p = 0;   //根节点
		for (int i = 0; i < s.length; i++) {
			if (tree[p].next[s[i] - 'a'] == 0) {
				tree[p].next[s[i] - 'a'] = ++tot;
				tree[tot] = new Tree();
			}
			p = tree[p].next[s[i] - 'a'];
		}
		
		//如果没有重复，则赋值
		if (tree[p].number == 0)
			tree[p].number = num;

	}

	
	//深度遍历
	static void query(int p) {
		
		for (int i = 0; i < 26; i++) {
			if (tree[p].next[i] != 0) {
				int y = tree[p].next[i];
				if (tree[y].number != 0)  //不为0则表示是单词，而且先输出的字典序肯定小于后输出的
					System.out.println((source[tree[y].number]));
				query(y);
			}
		}
	}

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int index = 1;   //单词的位置  
		tree[0] = new Tree();  //初始化根节点
		while (scanner.hasNextLine()) {
			String str = scanner.nextLine().toLowerCase();  //读一行文本
			String temp = "";
			for (int i = 0; i < str.length(); i++) {
				if (str.charAt(i) < 'a' || str.charAt(i) > 'z')  //如果不是a-z则表示要分割，我们插入一个“ ”方便后面的分割
					temp += " ";
				else
					temp += str.charAt(i);   //如果是a-z,则插入
			}
			String s[] = temp.split(" ");   //分割
			
			for (int j = 0; j < s.length; j++) {
				if (!s[j].equals("")) {
					source[index] = s[j];   //保存单词，方便后面的输出
					insert(s[j].toCharArray(), index++);   //插入字典树
				}
			}

		}
		query(0);   //从根开始遍历

	}

}
```


---

## 作者：d3NtMDAw (赞：0)

给楼下补充一下，论如何不使用c++11的auto   
其实就是把
```cpp
 for (auto& x : s) 
```
修改成
```cpp
for(int i=0;i<s.length();i++)
```
由于string已经定义了<运算符,直接保存单词集合到set即可

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
set<string> dict;
int main()
{
   string s,buf;
   while(cin>>s)
   {
       for(int i=0;i<s.length();i++)
       {
           if(isalpha((int)s[i])) s[i]=tolower(s[i]);
           else
             s[i]=' ';
        }  
        stringstream ss(s);
          while(ss>>buf)
          dict.insert(buf);
   }
   for(set<string>::iterator it =dict.begin();it!=dict.end();++it)
   {
       cout<<*it<<endl;
   }
   return 0;
}

---


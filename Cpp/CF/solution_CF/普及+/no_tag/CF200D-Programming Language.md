# Programming Language

## 题目描述

Recently, Valery have come across an entirely new programming language. Most of all the language attracted him with template functions and procedures. Let us remind you that templates are tools of a language, designed to encode generic algorithms, without reference to some parameters (e.g., data types, buffer sizes, default values).

Valery decided to examine template procedures in this language in more detail. The description of a template procedure consists of the procedure name and the list of its parameter types. The generic type T parameters can be used as parameters of template procedures.

A procedure call consists of a procedure name and a list of variable parameters. Let's call a procedure suitable for this call if the following conditions are fulfilled:

- its name equals to the name of the called procedure;
- the number of its parameters equals to the number of parameters of the procedure call;
- the types of variables in the procedure call match the corresponding types of its parameters. The variable type matches the type of a parameter if the parameter has a generic type T or the type of the variable and the parameter are the same.

You are given a description of some set of template procedures. You are also given a list of variables used in the program, as well as direct procedure calls that use the described variables. For each call you need to count the number of procedures that are suitable for this call.

## 样例 #1

### 输入

```
4
void f(int,T)
void  f(T, T)
 void foo123   ( int,  double,  string,string  ) 
  void  p(T,double)
3
int a
 string    s
double x123 
5
f(a,  a)
  f(s,a   )
foo   (a,s,s)
 f  (  s  ,x123)
proc(a)
```

### 输出

```
2
1
0
1
0
```

## 样例 #2

### 输入

```
6
void f(string,double,int)
void f(int)
   void f  ( T  )
void procedure(int,double)
void f  (T, double,int)   
void f(string, T,T)
4
 int a
 int x
string  t
double  val  
5
f(t, a, a)
f(t,val,a)
f(val,a, val)
 solve300(val, val)
f  (x)
```

### 输出

```
1
3
0
0
2
```

# 题解

## 作者：HyyypRtf06 (赞：4)

~~思路显然，调试犯难，粗心一点，全部玩完~~

纯模拟，主要难点在输入。

讲解代码见

```
//Question Name: Programming Language
//Question Number: CodeForces 200D
//State: Accepted
//Time: 2020/8/24
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<set>
#include<map>
#include<vector>
using namespace std;
set<string> name_func;
const vector<string> Vector;//空vector，用于比较
map<string,vector<string> > func[1010];//func[i][str]代表以str为名的第i个函数的数据类型
map<string,string> inter;//储存数据类型
string Turn(string s,bool flag=true){//将所有的空格全部删掉
	for(int i=0;i<s.size();i++){
		if(s[i]==' '){
			s=s.substr(0,i)+s.substr(i+1);
			i--;
		}
	}
	if(flag){//若flag==true，说明前面有一个void，需要被截掉
		s=s.substr(4);
	}
	return s;
}
void Read_func(string s){
	string Name=s.substr(0,s.find('('));//先截取函数名
	name_func.insert(Name);
	vector<string> v;
	string type;
	int start=s.find('(')+1;
	for(int i=start;i<s.size();i++){//因为已经把所有的空格去除，所以无需考虑空格
		if(s[i]==','||s[i]==')'){
			type=s.substr(start,i-start);
			start=i+1;//更新起始点
			v.push_back(type);
		}
	}
	for(int i=0;;i++){
		if(func[i][Name]==Vector){//存储函数信息
			func[i][Name]=v;
			break;
		}
	}
	return;
}
void Read_inter(){//读取数据类型
	string s;
	string t;
	cin>>s>>t;
	inter[t]=s;
	return;
}
void Solve(string s){
	string Name=s.substr(0,s.find('('));
	vector<string> v;
	string type;
	int start=s.find('(')+1;
	for(int i=start;i<s.size();i++){
		if(s[i]==','||s[i]==')'){
			type=inter[s.substr(start,i-start)];
			start=i+1;
			v.push_back(type);
		}
	}//处理出函数信息，已经讲过，这里不再赘述
	int ans=0;
	for(set<string>::iterator it=name_func.begin();it!=name_func.end();it++){
		if(*it==Name){//名称不匹配
			for(int i=0;;i++){
				if(func[i][*it]==Vector){//结束了
					break;
				}
				if(func[i][*it].size()!=v.size()){//长度不匹配
					continue;
				}
				for(int j=0;j<v.size();j++){
					if(v[j]!=func[i][*it][j]&&func[i][*it][j]!="T"){//比较信息，不符合就退出
						goto Break;
					}
				}
				ans++;
				Break:;
			}
		}	
	}
	cout<<ans<<endl;
	return;
}
int main(){
//	freopen("Input.txt","r",stdin);
//	freopen("Output.txt","w",stdout);
	int N,M,K;
	cin>>N;
	getchar();//getline读回车，所以需要getchar掉空格
	for(int i=0;i<N;i++){
		string s;
		getline(cin,s);
		s=Turn(s);
		Read_func(s);
	}
	cin>>M;
	for(int i=0;i<M;i++){
		Read_inter();
	}
	cin>>K;
	getchar();//同理
	for(int i=0;i<K;i++){
		string str;
		getline(cin,str);
		str=Turn(str,false);
		Solve(str);
	}
	return 0;
}
```
The End.

---

## 作者：原子げんし (赞：3)

~~这道题蒟蒻写了200行，结果看看rng的代码只有60行？！~~
## 我讲讲自己的解法：大模拟
首先先分析题意：首先可以确定函数前的void是
废话，然后又可以确定类型名字只有小写字母，不可能出现这种东东：
```
int a,a;
```
也不会出现这玩意儿：
```
int a a;
```
那就好做了：
因为函数匹配的条件如下：

- 名字一样
- 类型数量一样
- 函数类型匹配（T可以单独考虑）

所以第一步是先去空格，然后统计一下函数的类型的个数（可以开一个struct），再然后匹配,但怎么统计函数的类型呢？

## 我想到了4进制（敲黑板）
T对应0，int对应1，string对应2，double对应3。
不考虑0的情况下匹配就方便多啦！

简单吗？看看代码吧。


首先是结构体部分，很简单，easy：
```cpp
struct node {
    string name;
    int num;
    vector<int>v;//存放4进制
    node() {}
    node(string Na,int Nu,vector<int>V) {
        name=Na,num=Nu,v=V;
    }

}t[1010];
```
然后删空格,左右括号，其实可以用STL写，但蒟蒻不会（%%%rng）

```cpp
string remove(string s) {
    string remove(string s) {
    for(int i=0;i<s.size();i++) {
        if(s[i]==' ') {
                s[i]='$';
        }
    }
    string t1;
    for(int i=0;i<s.size();i++) {
        if(s[i]=='$') {
            continue;
        }
        t1.push_back(s[i]);
    }
    return t1;
}
```
下面string转4进制：

```cpp
vector<int>to_four(string s) {
    string tmp;
    vector<int>v;
    s=s+',';
    for(int i=0;i<s.size();i++) {
        if(s[i]!=',') {
            tmp+=s[i];
        } else {
            v.push_back(mp[tmp]);
            tmp="";
        }
    }
    //for(int i=0;i<v.size();i++) {
    //    cout<<v[i];
    //}
    //cout<<endl;
    return v;
}
```
下面统计：

```
pair<vector<int>,string> skip(string s) {
    for(int i=0;i<s.size();i++) {
        if(s[i]==' '||s[i]=='('||s[i]==')') {
            s[i]='@';
        }
    }
    string t;
    for(int i=0;i<s.size();i++) {
        if(s[i]=='@') {
            continue;
        }
        t.push_back(s[i]);
    }
    return make_pair(to_four(t),t);
}
int cnt(string s) {
    int num=1;
    for(int i=0;i<s.size();i++) {
        if(s[i]==',') {
            num++;
        }
    }
    return num;
}
node work(string s) {
    if(s.size()>4&&s.substr(0,4)=="void") {
        s.erase(0,4);
    }
    int idx=0;
    for(int i=0;i<s.size();i++) {
        if(s[i]=='(') {
            idx=i;
            break;
        }
    }
    string name=s.substr(0,idx);
    s.erase(0,idx);
    int num=cnt(s);
    vector<int>v=skip(s).first;
    string t=skip(s).second;
    //for(int i=0;i<v.size();i++) {
    //    cout<<v[i];
    //}
    //cout<<endl;
    return node(name,num,v);
}
```
最后统计ans：

```
int ays(node a) {
    int sum=0;
    for(int i=0;i<n;i++) {
        vector<int>v=a.v;
        int num=a.num;
        string s=a.name;
        s=remove(s);
        vector<int>v2=t[i].v;
        int num2=t[i].num;
        string s2=t[i].name;
        s2=remove(s2);
        if(s2.size()>4) {
            string TMP=s2.substr(0,4);
            if(TMP=="void") {
                s2.erase(0,4);
            }
        }
        //cout<<s<<' '<<s2<<endl;
        if(num!=num2||s!=s2) {
            continue;
        }
        bool good=1;
        for(int j=0;j<v.size();j++) {
            if(v[j]==0||v2[j]==0) {
                continue;
            }
            if(v[j]!=v2[j]) {
                good=0;
                break;
            }
        }
        sum+=good;
    }
    return sum;
}
```







最后完整代码：
```
#include<bits/stdc++.h>
using namespace std;
map<string,int>mp;
int n,m,k;
struct node {
    string name;
    int num;
    vector<int>v;
    node() {}
    node(string Na,int Nu,vector<int>V) {
        name=Na,num=Nu,v=V;
    }
    
}t[1010];
string remove(string s) {
    for(int i=0;i<s.size();i++) {
        if(s[i]==' ') {
                s[i]='@';
        }
    }
    string t1;
    for(int i=0;i<s.size();i++) {
        if(s[i]=='@') {
            continue;
        }
        t1.push_back(s[i]);
    }
    return t1;
}
vector<int>to_four(string s) {
    string tmp;
    vector<int>v;
    s=s+',';
    for(int i=0;i<s.size();i++) {
        if(s[i]!=',') {
            tmp+=s[i];
        } else {
            v.push_back(mp[tmp]);
            tmp="";
        }
    }
    //for(int i=0;i<v.size();i++) {
    //    cout<<v[i];
    //}
    //cout<<endl;
    return v;
}
pair<vector<int>,string> skip(string s) {
    for(int i=0;i<s.size();i++) {
        if(s[i]==' '||s[i]=='('||s[i]==')') {
            s[i]='$';
        }
    }
    string t;
    for(int i=0;i<s.size();i++) {
        if(s[i]=='$') {
            continue;
        }
        t.push_back(s[i]);
    }
    return make_pair(to_four(t),t);
}
int cnt(string s) {
    int num=1;
    for(int i=0;i<s.size();i++) {
        if(s[i]==',') {
            num++;
        }
    }
    return num;
}
node work(string s) {
    if(s.size()>4&&s.substr(0,4)=="void") {
        s.erase(0,4);
    }
    int idx=0;
    for(int i=0;i<s.size();i++) {
        if(s[i]=='(') {
            idx=i;
            break;
        }
    }
    string name=s.substr(0,idx);
    s.erase(0,idx);
    int num=cnt(s);
    vector<int>v=skip(s).first;
    string t=skip(s).second;
    //for(int i=0;i<v.size();i++) {
    //    cout<<v[i];
    //}
    //cout<<endl;
    return node(name,num,v);
}
int ays(node a) {
    int sum=0;
    for(int i=0;i<n;i++) {
        vector<int>v=a.v;
        int num=a.num;
        string s=a.name;
        s=remove(s);
        vector<int>v2=t[i].v;
        int num2=t[i].num;
        string s2=t[i].name;
        s2=remove(s2);
        if(s2.size()>4) {
            string TMP=s2.substr(0,4);
            if(TMP=="void") {
                s2.erase(0,4);
            }
        }
        //cout<<s<<' '<<s2<<endl;
        if(num!=num2||s!=s2) {
            continue;
        }
        bool good=1;
        for(int j=0;j<v.size();j++) {
            if(v[j]==0||v2[j]==0) {
                continue;
            }
            if(v[j]!=v2[j]) {
                good=0;
                break;
            }
        }
        sum+=good;
    }
    return sum;
}
int main() {
    mp["T"]=0;
    mp["int"]=1;
    mp["string"]=2;
    mp["double"]=3;
    cin>>n;
    getchar();
    for(int i=0;i<n;i++) {
        string s;
        getline(cin,s);
        t[i]=work(s);
        //cout<<t[i].name<<' '<<t[i].num<<endl;
    }
    cin>>m;
    getchar();
    while(m--) {
        string s;
        getline(cin,s);
        int idx=0;
        for(int i=0;i<s.size();i++) {
            if(s[i]==' ') {
                s[i]='$';
            }
        }
        string t1;
        for(int i=0;i<s.size();i++) {
            if(s[i]=='$') {
                continue;
            }
            t1.push_back(s[i]);
        }
        if(t1.size()>1) {
            string t2=t1.substr(0,1);
            string t3=t1;
            t3.erase(0,1);
            if(t2=="T") {
                mp[t3]=0;
            }
        }
        if(t1.size()>3) {
            string t2=t1.substr(0,3);
            string t3=t1;
            t3.erase(0,3);
            if(t2=="int") {
                mp[t3]=1;
            }
        }
        if(t1.size()>6) {
            string t2=t1.substr(0,6);
            string t3=t1;
            t3.erase(0,6);
            if(t2=="string") {
                mp[t3]=2;
            }
        }
        if(t1.size()>6) {
            string t2=t1.substr(0,6);
            string t3=t1;
            t3.erase(0,6);
            if(t2=="double") {
                mp[t3]=3;
            }
        }
    }
    cin>>k;
    getchar();
    for(int i=0;i<k;i++) {
        string buf;
        getline(cin,buf);
        cout<<ays(work(buf));
        puts("");
    }
    return 0;
}
```


---

## 作者：iiawaKL (赞：2)

# 蒟蒻写题解啦awa

这道题的题目意思很恶心。。。

话不多说，我们来看题。

这道题看似简单，（其实确实很简单），但是特别麻烦，很容易想到，可以纯模拟，然后检验输出。

 _Code->_ 
 
 ```
#include<bits/stdc++.h>
using namespace std;
int n,m,o;
struct proc{
	string name;
	vector<string> v;
}a[1010],b[1010];
map<string,string> mp;
int main(){
	cin>>n;
	string z;
	getline(cin,z);
	for(int i=0;i<n;i++){
		a[i].name="";
		string s;
		getline(cin,s);
		string t="";
		int j;
		for(j=0;j<s.size();j++){
			if(s[j]!=' ')break;
		}
		int p;
		for(p=s.size()-1;p>=0;p--){
			if(s[p]!=' ')break;
		}
		for(int l=j;l<=p;l++){
			if(s[l]==' ')continue;
			t+=s[l];
		}
		bool flag=0;
		for(int l=4;l<t.size();l++){
			if(t[l]=='(')flag=1;
			if(!flag&&t[l]!=' ')a[i].name+=t[l];
			if(flag){
				if(t[l]=='i'){
					l+=3;
					a[i].v.push_back("int");
				}
				else if(t[l]=='s'){
					l+=6;
					a[i].v.push_back("string");
				}
				else if(t[l]=='d'){
					l+=6;
					a[i].v.push_back("double");
				}
				else if(t[l]=='T'){
					l++;
					a[i].v.push_back("T");
				}
			}
		}
	}
	cin>>m;
	getline(cin,z);
	for(int i=0;i<m;i++){
		b[i].name="";
		string s;
		getline(cin,s);
		string t="";
		int j;
		for(j=0;j<s.size();j++){
			if(s[j]!=' ')break;
		}
		int p;
		for(p=s.size()-1;p>=0;p--){
			if(s[p]!=' ')break;
		}
		for(int l=j;l<=p;l++){
			if(s[l]==' ')continue;
			t+=s[l];
		}
		string r="";
		if(t[0]=='i'){
			for(int l=3;l<t.size();l++){
				if(t[l]==' ')continue;
				r+=t[l];
			}
			mp[r]="int";
		}
		if(t[0]=='s'){
			for(int l=6;l<t.size();l++){
				if(t[l]==' ')continue;
				r+=t[l];
			}
			mp[r]="string"; 
		}
		if(t[0]=='d'){
			for(int l=6;l<t.size();l++){
				if(t[l]==' ')continue;
				r+=t[l];
			}
			mp[r]="double";
		}
	}
	cin>>o;
	getline(cin,z);
	for(int i=0;i<o;i++){
		string s;
		getline(cin,s);
		string t="";
		int j;
		for(j=0;j<s.size();j++){
			if(s[j]!=' ')break;
		}
		int p;
		for(p=s.size()-1;p>=0;p--){
			if(s[p]!=' ')break;
		}
		for(int l=j;l<=p;l++){
			if(s[l]==' ')continue;
			t+=s[l];
		}
		bool flag=0;
		for(int l=0;l<t.size();l++){
			if(t[l]=='(')flag=1;
			if(!flag&&t[l]!=' '){b[i].name+=t[l];continue;} 
			if(t[l]!='('&&t[l]!=' '&&t[l]!=')'&&t[l]!=','){
				string u="";
				int l2;
				for(l2=l;l2<t.size();l2++){
					if(t[l2]==' '||t[l2]=='('||t[l2]==')'||t[l2]==',')break;
					u+=t[l2];
				}
				l=l2-1;
				b[i].v.push_back(mp[u]);
			}
		}
		int ans=0;
		for(int l=0;l<n;l++){
			if(a[l].name==b[i].name&&a[l].v.size()==b[i].v.size()){
				bool flag=0;
				for(int l2=0;l2<a[l].v.size();l2++){
					if(a[l].v[l2]!=b[i].v[l2]&&a[l].v[l2]!="T")flag=1;
				}
				if(!flag)ans++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：YFF1 (赞：1)

## 题目分析：
一道经典模拟题，非常考验人的耐心和细节。可以先把给定函数和函数调用语句中的几个需要匹配的部分拆解下来，然后再挨个对照，看一些是不是都能对的上。
## 代码（奇丑无比，奆佬们不要在意）：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
string s,s2,s0;
map<string,string>mp;
struct node{
	string name="";
	string type[10]={""};
	int l;//共有l个用于匹配的部分 
}a[1005],b[1005];
int main () {
	cin>>n;
	getline(cin,s0);
	for(int i=1;i<=n;i++){
		getline(cin,s);
		int pos=s.find('(');
		int pos2=s.find('d')+1;
		bool f=1;
		while(s[pos]==' ')pos--;
		while(f=1){
			if(s[pos2]==' ')pos2++;
			else if(s[pos2]=='('){
				pos2--;
				break;
			}
			else {
				a[i].name+=s[pos2];//拆解过程名 
				pos2++;
			}
		}
		int pos3=s.find('(')+1;
		int t=1;
		while(pos3<s.size()){
			if(s[pos3]==')')break;
			if(s[pos3]==','||s[pos3]=='(')t++; 
			else if(s[pos3]==' '){
				pos3++;
				continue;
			}
			else a[i].type[t]+=s[pos3];//拆解变量名
			pos3++;
		}
		a[i].l=t; 
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>s>>s2;
		mp[s2]=s;//知道函数调用语句中各个名字所属类型 
	}
	cin>>k;
	getline(cin,s0);
	for(int i=1;i<=k;i++){
		getline(cin,s);
		int pos=s.find('(');
		int pos2=0;
		bool f=1;
		while(s[pos]==' ')pos--;
		while(f=1){
			if(s[pos2]==' ')pos2++;
			else if(s[pos2]=='('){
				pos2--;
				break;
			}
			else {
				b[i].name+=s[pos2];//拆解过程名 
				pos2++;
			}
		}
		int pos3=s.find('(')+1;
		int t=1;
		while(pos3<s.size()){
			if(s[pos3]==')')break;
			if(s[pos3]==','||s[pos3]=='(')t++; 
			else if(s[pos3]==' '){
				pos3++;
				continue;
			}
			else b[i].type[t]+=s[pos3];//拆解变量名
			pos3++;
		}
		b[i].l=t; 
		for(int j=1;j<=t;j++)b[i].type[j]=mp[b[i].type[j]];//替换为这个名字所属类型，方便匹配
	}
	for(int i=1;i<=k;i++){
		int cnt=0;
		for(int j=1;j<=n;j++){
			if(b[i].l==a[j].l&&b[i].name==a[j].name){
				bool f=1;
				for(int z=1;z<=a[j].l;z++){
					if((a[j].type[z]==b[i].type[z])||(a[j].type[z]=="T")||(b[i].type[z]=="T"))continue;
					else {
						f=0;
						break;
					}
				}
				if(f==1)cnt++;
			}
		}
		cout<<cnt<<endl;
	}
	return 0;
}

---

## 作者：Empty_Dream (赞：1)

### CF200D 解题报告

#### 题意

给你 $n$ 个函数，由**函数类型**、**函数名**和**参数类型**组成。

给你 $m$ 个变量，由**变量类型**和**变量名**组成。

给你 $k$ 个调用关系，由**调用的函数名**和**参数名**构成。

**参数类型**和**变量类型**保证为 `int`，`double`，`string` 和 `T` 中的一个，其中 `T` 表示可以匹配任意类型。

#### 分析

很明显，这是一道大模拟，可以先将函数给存储下来，变量名所对应的类型存储下来，最后调用的时候在判断符不符合就好了。

函数可以先将所有符号变成空格，然后使用 `vector` 将这个函数的每一项存进去，最后塞入一个大的 `vector` 进行存储。

变量直接使用一个 `map` 进行映射操作就好了。

查询时将调用函数按上面函数的处理方式处理后跟存储下来的函数进行比较，如果有相同就记录一次。

最后输出答案就~~切了~~一道绿题。

#### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m, k;
string s, a, b;
map<string, string> variable_type;//变量名所对应的变量类型
vector<vector<string>> function_type;//储存所有函数，内部的存的是每一个函数的参数类型

bool check(vector<string> a, vector<string> b){//判断是否能对的上，a是函数，b是调用
	if (a.size() - 1 != b.size()) return false;//长度
	if (a[1] != b[0]) return false;//判断函数名
	for (int i = 1; i < b.size(); i++){
		if (a[i + 1] != "T" && a[i + 1] != variable_type[b[i]]) return false;//类型
	}
	return true;
}

signed main(){
	scanf("%lld\n", &n);
	for (int i = 1; i <= n; i++){
		getline(cin, s);
		vector<string> name;
		for (char &c : s) if (c == '(' || c == ')' || c == ',') c = ' ';
		istringstream ss(s);//自动分离空格
		while (ss >> s) name.push_back(s);//将分离后的每一个字符串放入
		function_type.push_back(name);//将每一个函数放入
	} 
	scanf("%lld\n", &m);
	for (int i = 1; i <= m; i++){
		cin >> a >> b;
		variable_type[b] = a;//将变量名和类型对应起来
	}
	scanf("%lld\n", &k);
	for (int i = 1; i <= k; i++){
		int cnt = 0;
		getline(cin, s);
		vector <string> name;
		for (char &c : s) if (c == '(' || c == ')' || c == ',') c = ' ';
		istringstream ss(s);
		while (ss >> s) name.push_back(s);//同上，分离空格
		for (int j = 0; j < n; j++){
			if (check(function_type[j], name)) cnt++;
		}
		printf("%lld\n", cnt);
	}
	return 0;
}
```



---

## 作者：CarroT1212 (赞：1)

### 题目大意

给定 $m$ 个函数，格式为 `void 函数名(类型,类型,...,类型)`，其中类型包含 `int`、`double`、`string` 和 `T`（这个类型可以匹配传入的所有类型，有一点点像现实中的 `auto`）。输入的函数名以及参数可能会有重复。

然后给定 $n$ 个变量，格式为 `类型 变量名`，类型仍然为上述四个类型之一。

再给定 $k$ 个函数调用语句，格式为 `函数名(变量名,变量名,...,变量名)`，对于每个语句，输出这个语句可合法调用 $m$ 个函数中的多少个。不保证函数名和变量名都是上面输入过的。

注意输入每个符号周围都可能会出现空格，且连续的单词间可能会出现不止一个空格。

------------

### 解法分析

我们可以在输入函数调用语句时，每输入一个，就看看 $m$ 个函数中有几个是合法的，并注意一下判断时把变量名换成对应的类型即可。

~~讲了个寂寞。~~ 具体的实现细节见代码注释，这种题对来说用注释讲就是最好的方法。

------------

### 代码

对下面用到的 STL 不熟的自行百度。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e3+7;
ll m,k,t;
string oth,inp;
map <string,string> type; //type：用于记录每个变量的类型
map <string,vector<vector<string>>> bl;
//bl：bl[函数名]{{各个函数的类型}...{各个函数的类型}}
//因为有时候函数名会重复，所以我做了这样一个处理，到时直接搜以这个名字为函数名的函数即可
//其实想想感觉有点多此一举了，因为扫一遍所有 m 个函数也不是不可以，但是我懒得再打一遍了，这样也能过
int main() {
	cin>>m;
	for (ll i=1;i<=m;i++) {
		cin>>oth;
		getline(cin,inp);
		string nameq; //nameq：记录函数名
		ll sta=1; //sta：在下面的遍历时表示遍历的位置是函数名还是参数
		for (ll j=0;j<inp.size();j++) {
			char k=inp[j];
			if (k==' '||k==')') continue; //空格其实可以直接跳过，这样是没有影响的
			else if (k=='(') {
				sta=2; //到参数部分了
				vector <string> pback;
				if (inp[j+1]!=')') pback.push_back("");
				//有一种情况叫 void xxx()。（我不清楚数据里有没有这种函数，但是特判一下总是好一点嘛
				bl[nameq].push_back(pback);
			}
			else if (sta==1) nameq.push_back(k); //输入函数名（冷知识：string 可以 push_back，至少我很喜欢这样用
			else if (sta==2) {
				if (k==',') bl[nameq].back().push_back(""); //新的类型
				else bl[nameq].back().back().push_back(k);
			}
		}
	}
	cin>>k;
	for (ll i=1;i<=k;i++) {
		cin>>oth>>inp;
		type[inp]=oth; //记录类型
	}
	cin>>t;
	getchar();
	while (t--) {
		getline(cin,inp);
		string nameq;
		vector <string> tmp; //tmp：存储函数中的变量
		ll sta=1,ans=0;
		for (ll j=0;j<inp.size();j++) { //跟上面的写法差不多
			char i=inp[j];
			if (i==' '||i==')') continue;
			else if (i=='(') {
				sta=2;
				if (inp[j+1]!=')') tmp.push_back("");
			}
			else if (sta==1) nameq.push_back(i);
			else if (sta==2) {
				if (i==',') tmp.push_back("");
				else tmp.back().push_back(i);
			}
		}
		for (ll i=0;i<tmp.size();i++) tmp[i]=type[tmp[i]]; //转化为类型
		for (auto i:bl[nameq]) { //遍历以这个名字为函数名的函数
			if (i.size()!=tmp.size()) continue;
			ll flg=1;
			for (ll j=0;j<i.size();j++)
				if (i[j]!=tmp[j]&&i[j]!="T"&&tmp[j]!="T") { flg=0; break; } //注意这里对 T 类型的判断，别忘了
			ans+=flg;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：HMZHMZHMZ (赞：1)

## 题意
读入一个数 $ n $，接下来读入 $ n $ 行字符串，每一行有一个形如 ` void 函数名(参数列表) ` 的函数，每一个函数中最多有 $ 5 $ 个变量。

再读入一个数 $ m $，接下来读入 $ m $ 行字符串，每一行有一个形如 ` 变量类型 变量名 ` 的变量。变量类型有四个，包括 ` string `，` int `，` double ` 和 ` T `。

再读入一个数 $ k $，接下来读入 $ k $ 行字符串，每一行给定一个函数调用语句，问能正常调用几个函数。

## 思路

因为 $ 1 \leq n $，$ m $，$ k \leq 1000 $，所以可以暴力。每一次先找出调用函数中数字的类型，然后再依次判断是否匹配即可。

时间复杂度 $ O ( k ( n + m ) ) $，显然能过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1011;
struct node{
	string id;
	int p[6],len;//1:int,2:string,3:double,4:T
	void init(){memset(p,-1,sizeof(p));}
}a[N];
struct bl{
	string id;
	int p;
}b[N];
int n,m,k,cnt,ans[N];
string s,s1;
int main(){
	scanf("%d\n",&n);
	for(register int i=1;i<=n;++i){
		getline(cin,s);
		s1="";
		int l=0;
		a[i].init();
		for(register int j=0;j<s.size();++j){
			if(s[j]=='(') a[i].id=s1,s1="";
			else if(s[j]==' '&&s1=="void") s1="";
			else if(s[j]==' ') continue;
			else if(s[j]==','||s[j]==')'){
				int opt;
				if(s1=="int") opt=1;
				else if(s1=="string") opt=2;
				else if(s1=="double") opt=3;
				else opt=4;
				s1="";
				l++;
				a[i].p[l]=opt;
				a[i].len=l;
			}else s1=s1+s[j];
		}
	}
	scanf("%d\n",&m);
	for(register int i=1;i<=m;++i){
		getline(cin,s);
		s1="";
		s=s+":";
		for(register int j=0;j<=s.size();++j){
			if(s1=="int") s1="",b[i].p=1;
			else if(s1=="string") s1="",b[i].p=2;
			else if(s1=="double") s1="",b[i].p=3;
			else if(s1=="T") s1="",b[i].p=4;
			else if(s[j]==' ') continue;
			else if(s[j]==':') b[i].id=s1;
			else s1+=s[j];
		}
	}
	scanf("%d\n",&k);
	for(register int i=1;i<=k;++i){
		getline(cin,s);
		string now;
		cnt=0;
		s1="";
		for(register int j=0;j<s.size();++j){
			if(s[j]=='(') now=s1,s1="";
			else if(s[j]==','||s[j]==')'){
				cnt++;
				for(register int p=1;p<=m;++p){
					if(b[p].id==s1){
						ans[cnt]=b[p].p;
						break;
					}
				}
				s1="";
			}else if(s[j]==' ') continue;
			else s1+=s[j];
		}
		int sum=0;
		for(register int j=1;j<=n;++j){
			bool flag=0;
			if(a[j].id!=now||a[j].len!=cnt) continue;
			for(register int p=1;p<=cnt;++p){
				if(a[j].p[p]!=ans[p]&&a[j].p[p]!=4){
					flag=1;
					break;
				}				
			}
			if(!flag) sum++;
		}
		cout<<sum<<endl;
	}
	return 0;
}
```

---

## 作者：PDAST (赞：0)

一道模拟，竟然是绿！！！
## 题意
有一种语言，它有 $N$ 个函数，这些函数有固定传参格式，每一行规定一个函数，给出它的格式，形如
~~~
void 函数名(参数列表)
~~~
其中，类型可以为 `string`、`int`、`double` ，和一个通用泛类型 `T` 。再给出 $M$ 个变量定义，形如 
~~~
类型 变量名
~~~
类型可以为 `string`、`int`、`double` 。最后给出 $K$ 条语句，每次引用一个函数，求符合这些语句形式的函数有多少个。
## 分析
题意是真的长，作为一道模拟，在迷惑人的角度上，他已经很成功了。我们唯一需要做的只是去暴力模拟，代码也不长，只有一千两百多字，所以，开干！
## 思路
我们先去掉函数前的 `void` ，把函数形式压缩成没有空格的样子，再记录每个变量的类型，最后把调用语句转化成函数的形式，再比对，判断是否与原有函数格式相同即可。
## 实现
我们分块实现代码。第一步，存储函数，每次输入一行，跳过 `void` 后开始存储函数，只要不是空格就放进录入，输完后加入一个键为 string 值为 bool 的 map 里。第二步，录入函数，每次输入两个字符串，也放进一个 map 里，表示该变量的类型。第三步，执行语句并统计，我们把语句提取出来，并把变量转化为相应的类型，这里有一个难点，因为题目中会有一个通用泛类型，所以我们考虑存储原类型后递归处理。怎么递归呢？定义一个 int 类型的函数，每次有两条分叉，第一条是加入原类型，第二条是加入 `T` ，到最后，判断是否有该函数，直接返回值（$1$ 或 $0$）即可，这就是答案。
## 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
string type[4]={"T","int","string","double"};
map<string,bool>pro;
map<string,string>var;
string _std[11];
int cou;
int cnt(string st,int num){
	string s1,s2;
	s1=st+_std[num];
	s2=st+"T";
	if(num==cou){
		s1+=")";
		s2+=")";
		return pro[s1]+pro[s2];
	}else{
		s1+=",";
		s2+=",";
		return cnt(s1,num+1)+cnt(s2,num+1);
	}
}
int main() {
	int n,m,k;
	cin>>n;
	getchar();
	for(int i=1;i<=n;i++){
		string st,s;
		getline(cin,st);
		int len=st.size();
		for(int j=0;j<len;j++){
			if(st[j]!=' '){
				s+=st[j];
			}
			if(s=="void"){
				s.clear();
			}
		}
		pro[s]=1;
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		string s1,s2;
		cin>>s1>>s2;
		var[s2]=s1;
	}
	cin>>k;
	getchar();
	for(int i=1;i<=k;i++){
		string st,s;
		getline(cin,st);
		int j=0,tmp=0,len=st.size();
		while(st[j]!='('&&j<len){
			if(st[j]!=' '){
				s+=st[j];
			}
			j++;
		}
		j++;
		int c=0;
		for(;j<st.size();j++){
			string t;
			while(st[j]!=','&&j<len&&st[j]!=')'){
				if(st[j]!=' '){
					t+=st[j];
				}
				j++;
			}
			if(t!=""){
				c++;
				_std[c]=var[t];	
			}
		}
		cou=c;
		s+="(";
		cout<<cnt(s,1)<<"\n";
	}
	return 0;
}
~~~

---

## 作者：Peaky (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF200D)

**题目大意**

给定若干个函数，每个函数形如

```
void 函数名(参数列表（仅有类型）)
```
其中参数列表中可能是 ``` int ,double ,string ``` 和 ``` T ``` 类型（可匹配所有类型）

又给定若干个变量，每个变量形如

```
变量类型 变量名
```

给定若干个函数调用语句，问每个语句能与多少个函数产生调用关系。

**Part 1**

---

先用一个 ``` map ``` 去映射各个数据类型，如下：

```cpp
mp[""]=-1;
mp["T"]=0;
mp["string"]=1;
mp["int"]=2;
mp["double"]=3;
```

再用一个 ``` state ``` 去判断输入的状态，如下：

```cpp
for(state=1;state<=5;state++){
	bool flag=0;
	string t="";
	while(cin>>c){
		if(c==' '&&t=="") continue;
		if(c==')'){
			flag=1;
			break;
		}
		if(c==',') break;
				t+=c;
	}
	if(state==1) name[i].t1=mp[t];
	if(state==2) name[i].t2=mp[t];
	if(state==3) name[i].t3=mp[t];
	if(state==4) name[i].t4=mp[t];
	if(state==5) name[i].t5=mp[t];
	if(flag) break;
}
```

- 其中 $ state = 1 $ 的状态是存储第一个类型，  
- $ state = 2 $ 的状态是存储第二个类型，  
- $ state = 3 $ 的状态是存储第三个类型，  
- $ state = 4 $ 的状态是存储第四个类型，  
- $ state = 5 $ 的状态是存储第五个类型。  

**Part2**

---

再读入每个变量的类型

```cpp
cin>>n;
for(int i=1;i<=n;i++){
	string v,na;
	cin>>v>>na;
	turn[na]=v;
}
```

**Part3**

---

最后再依次对比每一个与当前函数名相同的函数

```cpp
cin>>n;
for(int i=1;i<=n;i++){
	char c;
	string get;
	while(cin>>c){
		if(c=='('||get.size()&&c==' ') break;
		get+=c;
	}
	int state,t1,t2,t3,t4,t5;
	t1=t2=t3=t4=t5=-1;
	for(state=1;state<=5;state++){
		bool flag=0;
		string t="";
		while(cin>>c){
			if(c==' '&&t=="") continue;
			if(c==')'){
				flag=1;
				break;
			}
			if(c==',') break;
			t+=c;
		}
		if(state==1) t1=mp[turn[t]];
		if(state==2) t2=mp[turn[t]];
		if(state==3) t3=mp[turn[t]];
		if(state==4) t4=mp[turn[t]];
		if(state==5) t5=mp[turn[t]];
		if(flag) break;
	}
	int cnt=0;
	for(int i=1;i<=m;i++){
		if(name[i].na==get&&name[i].gs==state){
			if((t1==name[i].t1||!name[i].t1)&&(t2==name[i].t2||!name[i].t2)&&(t3==name[i].t3||!name[i].t3)&&(t4==name[i].t4||!name[i].t4)&&(t5==name[i].t5||!name[i].t5)){
				cnt++;
			}
		}
	}
	cout<<cnt<<endl;
}
```

``` T ``` 的类型是可以匹配所有的类型的，所以需要特殊判断。

```cpp
if((t1==name[i].t1||!name[i].t1)&&(t2==name[i].t2||!name[i].t2)&&(t3==name[i].t3||!name[i].t3)&&(t4==name[i].t4||!name[i].t4)&&(t5==name[i].t5||!name[i].t5))
{
	cnt++;
}
```

最后附上蒟蒻的代码

```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*


*/
struct Node{
	string na;
	int t1,t2,t3,t4,t5,gs;
}name[N];
map<string,int> mp;
map<string,string> turn;
int main(){
	int n,m;
	cin>>m;
	mp[""]=-1;
	mp["T"]=0;
	mp["string"]=1;
	mp["int"]=2;
	mp["double"]=3;
	
/*----------------------------------part1--------------------------------------*/	
	
	for(int i=1;i<=m;i++){
		string v;
		cin>>v;
		char c;
		int cnt=-1;
		name[i].t1=name[i].t2=name[i].t3=name[i].t4=name[i].t5=-1;
		while(cin>>c){
			if(c=='('||name[i].na.size()&&c==' ') break;
			name[i].na+=c;
		}
		int state;
		for(state=1;state<=5;state++){
			bool flag=0;
			string t="";
			while(cin>>c){
				if(c==' '&&t=="") continue;
				if(c==')'){
					flag=1;
					break;
				}
				if(c==',') break;
				t+=c;
			}
			if(state==1) name[i].t1=mp[t];
			if(state==2) name[i].t2=mp[t];
			if(state==3) name[i].t3=mp[t];
			if(state==4) name[i].t4=mp[t];
			if(state==5) name[i].t5=mp[t];
			if(flag) break;
		}
		name[i].gs=state;
	}
	
/*----------------------------------part2--------------------------------------*/	
	
	cin>>n;
	for(int i=1;i<=n;i++){
		string v,na;
		cin>>v>>na;
		turn[na]=v;
	}
	
/*----------------------------------part3--------------------------------------*/	
	
	cin>>n;
	for(int i=1;i<=n;i++){
		char c;
		string get;
		while(cin>>c){
			if(c=='('||get.size()&&c==' ') break;
			get+=c;
		}
		int state,t1,t2,t3,t4,t5;
		t1=t2=t3=t4=t5=-1;
		for(state=1;state<=5;state++){
			bool flag=0;
			string t="";
			while(cin>>c){
				if(c==' '&&t=="") continue;
				if(c==')'){
					flag=1;
					break;
				}
				if(c==',') break;
				t+=c;
			}
			if(state==1) t1=mp[turn[t]];
			if(state==2) t2=mp[turn[t]];
			if(state==3) t3=mp[turn[t]];
			if(state==4) t4=mp[turn[t]];
			if(state==5) t5=mp[turn[t]];
			if(flag) break;
		}
		int cnt=0;
		for(int i=1;i<=m;i++){
			if(name[i].na==get&&name[i].gs==state){
				if((t1==name[i].t1||!name[i].t1)&&(t2==name[i].t2||!name[i].t2)&&(t3==name[i].t3||!name[i].t3)&&(t4==name[i].t4||!name[i].t4)&&(t5==name[i].t5||!name[i].t5)){
					cnt++;
				}
			}
		}
		cout<<cnt<<endl;
	}
	return 0;
}
```

华丽 ```over```

---

## 作者：Sexy_Foxy (赞：0)

## 题意：

定义一些函数，定义一些变量，最后给出几个变量名，求能调用到多少函数？

## 解题思路：

虽然题面可能会有点恶心，但理解之后真不难。这道题一看就是一道大模拟，模拟过程如下所述。

### 第一步：

首先要知道这题要考察的内容。这道题主要是靠如何输入和查找。

### 第二步：

#### 首先是输入部分：

看着样例输入一大串的带空格字符串，不要慌张，仔细看看。首先，由题意可得，后面查找的函数名不带前缀的返回值类型，但输入却会带一个前缀的返回值类型，咋办呢？其实不需要太多处理，我们只需要用一点小技巧（~~卡BUG~~），用一个字符串读掉即可。而函数名再去掉空格和返回值类型后只需要判断当前字符是否是 $<$ 即可，而后面的参数类型只需要以 $,$ 和 $>$为分界即可。

#### 然后是查找部分：

查找的东西总得有个东西存吧。我们可以用一个数组存，然后遍历，时间复杂度是 $O(n)$ ，但这种方法虽然不超时，但既耗时又麻烦，有什么更好的解决方法吗？有的。我们可以用万能的 **STL** 中的 [map](https://blog.csdn.net/m0_67402564/article/details/126317891) （不知道 map 怎么用的这里给出了链接）来存储，直接通过下标的方式直接访问，时间复杂度是 $O(\log n)$ ，即快速又省力。

### 第三步：

接下来把各部分代码分解开来讲解：

#### 定义部分：

```
#include<bits/stdc++.h>
using namespace std;
map<string,vector<vector<string> > >fun; //存储和查找函数名
map<string,string>type; //存储和查找变量名
int n,m,k;
```

#### 去除空格：

```
string get_space(string s)
{
	for(int i=0;i<s.size();i++)
	{
		if(s[i]==' ')
		{
			s=s.substr(0,i)+s.substr(i+1); //获取空格前和空格后的字符串
			i--; //不减会出BUG
		}
	}
	return s;
}
```

#### 定义函数：

```
scanf("%d",&n);
while(n--)
{
	string qwq,s;
	cin>>qwq; //处理void
	getline(cin,s); //输入没有void的字符串
	s=get_space(s);
	int start=0;
	string name; //存储函数名
	while(s[start]!='(')
	{
		name+=s[start++];
	}
	string x; //获取定义类型
	vector<string>a; //定义类型的数组
	for(int i=start+1;i<s.size();i++)
	{
		if(s[i]==','||s[i]==')') //判断定义类型是否结束
		{
			a.push_back(x); //将得到的定义类型存入数组
			x.clear(); //清空字符串
		}
		else
		{
			x+=s[i];
		}
	}
	fun[name].push_back(a); //将数组存入map
}
```

#### 定义变量：

```
scanf("%d",&m);
while(m--)
{
	string ty,name;
	cin>>ty>>name;
	type[name]=ty; //将变量存入map
}
```

#### 调用部分：

```
scanf("%d",&k);
getchar(); //读掉空行，去掉会出大BUG
while(k--)
{
	string s;
	getline(cin,s);
	s=get_space(s); //去掉空格
	int start=0;
	string name; //获取函数名
	while(s[start]!='(')
	{
		name+=s[start++];
	}
	vector<string>a; //存储变量的数组
	string x; //获取变量名
	for(int i=start+1;i<s.size();i++)
	{
		if(s[i]==','||s[i]==')') //判断变量名是否结束
		{
			a.push_back(x); //将变量名存入数组
			x.clear(); //清空字符串
		}
		else
		{
			x+=s[i];
		}
	}
	int ans=0; //保存能调用多少个
	for(int i=0;i<fun[name].size();i++)
	{
		vector<string>sum=fun[name][i]; //获取函数
		if(sum.size()!=a.size()) //如果元素个数不一样直接跳过
		{
			continue;
		}
		bool flag=true; //判断是否可以调用
		for(int j=0;j<sum.size();j++)
		{
			if(type[a[j]]!=sum[j]&&type[a[j]]!="T"&&sum[j]!="T") //判断定义类型是否一致
			{
				flag=false;
				break;
			}
		}
		if(flag)
		{
			ans++;
		}
	}
	printf("%d\n",ans);
}
```

## 完整的Code：

整整 $108$ 行的代码！

```
#include<bits/stdc++.h>
using namespace std;
map<string,vector<vector<string> > >fun;
map<string,string>type;
int n,m,k;
string get_space(string s)
{
	for(int i=0;i<s.size();i++)
	{
		if(s[i]==' ')
		{
			s=s.substr(0,i)+s.substr(i+1);
			i--;
		}
	}
	return s;
}
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		string qwq,s;
		cin>>qwq;
		getline(cin,s);
		s=get_space(s);
		int start=0;
		string name;
		while(s[start]!='(')
		{
			name+=s[start++];
		}
		string x;
		vector<string>a;
		for(int i=start+1;i<s.size();i++)
		{
			if(s[i]==','||s[i]==')')
			{
				a.push_back(x);
				x.clear();
			}
			else
			{
				x+=s[i];
			}
		}
		fun[name].push_back(a);
	}
	scanf("%d",&m);
	while(m--)
	{
		string ty,name;
		cin>>ty>>name;
		type[name]=ty;
	}
	scanf("%d",&k);
	getchar();
	while(k--)
	{
		string s;
		getline(cin,s);
		s=get_space(s);
		int start=0;
		string name;
		while(s[start]!='(')
		{
			name+=s[start++];
		}
		vector<string>a;
		string x;
		for(int i=start+1;i<s.size();i++)
		{
			if(s[i]==','||s[i]==')')
			{
				a.push_back(x);
				x.clear();
			}
			else
			{
				x+=s[i];
			}
		}
		int ans=0;
		for(int i=0;i<fun[name].size();i++)
		{
			vector<string>sum=fun[name][i];
			if(sum.size()!=a.size())
			{
				continue;
			}
			bool flag=true;
			for(int j=0;j<sum.size();j++)
			{
				if(type[a[j]]!=sum[j]&&type[a[j]]!="T"&&sum[j]!="T")
				{
					flag=false;
					break;
				}
			}
			if(flag)
			{
				ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

## 后记：

这篇题解花了我半天时间，如有错误请私聊！

注：本题解中的链接中的内容非本蒟蒻所写

#### qwq

---

## 作者：Jerrywang09 (赞：0)

# 先说几句

这题只是一道很恶心的字符串处理。放轻松，没有什么深奥的算法。也考察了对于结构体的理解。

# 解题思路

先建立一个结构体。结构体的第一个成员是函数的名称，第二个成员是函数的参数类型列表。用 vector 存储。

首先输入 $n1$，是函数的数量。特别注意，如果下面要 getling 输入字符串，要用
```cpp
cin.get();
```
把换行符吃掉。

特别注意，以下三个部分的调用，都用可读取空格的 getline 函数。

具体写法：
```cpp
getline(cin, 字符串名称);
```

## Part 1 读入函数

先 getline 一个字符串，称之为 $s$。

先去除字符串最前面的空格。

再用 erase 函数去掉函数类型 void。

再次去除最前面的空格。

在读到表示参数的左括号前，先将函数名保存下来。
**还是注意，要忽略空格。**

将当前函数的 name 先保存进函数的结构体数组。

接下来，对于每个字符，只要其不是
**空格，逗号，右括号**，
就将其加入当前函数的参数列表中。

遇到逗号，就说明马上要开始有一个新参数了。

遇到右括号，那么当前函数的处理就大功告成了！

## Part 2 读入变量

还是相同的方法，读入 $n2$。
这边的处理比上面简单多了。只要用
```cpp
cin>>s1>>s2;
```
就可以读进变量类型和变量名称。用一个哈希表 map，就可以存储变量的相关信息。

## Part 3 处理调用

按照 Part 1 的类似办法，读入每一个处理调用信息。
读取函数名和实参列表。

先令 $cnt$=0。

在函数库中寻找该函数名所对应的函数，遇到函数名相同的，判断参数数量和类型是否相同。我的程序中用了重载 == 运算符来判断。

对于百搭的 T 类型，可以直接 continue 掉。我的[另外一篇题解](https://jerrywzr.blog.luogu.org/solution-cf138a)有这种思路的详细解释。

只要匹配上的函数库中的函数，$cnt$++。对于每一个提问，输出 $cnt$ 即可。

这样，你就可以写出程序了！

# 奉上代码

千万不要抄，小心棕名！
```cpp
// 200D Programming Language
#include <bits/stdc++.h>
using namespace std;

struct functions
{
	string name;		// 名称 
	vector<string> ps;	// 参数 
};

bool operator ==(functions a, functions b)
{
	if(a.name!=b.name)
		return false;
	if(a.ps.size()!=b.ps.size())
		return false;
	for(int i=0; i<a.ps.size(); i++)
	{
		if(a.ps[i]=="T")
			continue;
		else if(a.ps[i]!=b.ps[i])
			return false;
	}		
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n1; cin>>n1;
	functions f[n1];
	cin.get();
	string s;
	for(int k=0; k<n1; k++)
	{
		getline(cin, s);
		int i=0;
		while(s[i++]==' ') ;	// 去除前面的空格
		s.erase(0, i-1);
		s.erase(0, 4);		// 去除前面的void
		i=0;
		while(s[i++]==' ') ;	// 去除前面的空格
		s.erase(0, i-1);
		//cout<<s<<endl;
		string name;
		for(i=0; i<s.find("("); i++)
			if(s[i]!=' ')
				name+=s[i];
		i++;
		f[k].name=name;
		string type;
		for(; i<s.size(); i++)
			if(s[i]!=' ' && s[i]!=',' && s[i]!=')')
				type+=s[i];
			else if(s[i]==',' || s[i]==')')
			{
				f[k].ps.push_back(type);
				type.clear();
			}
	}
	
	/*
	for(int i=0; i<n1; i++)
	{
		cout<<f[i].name<<endl;
		for(int j=0; j<f[i].ps.size(); j++)
			cout<<f[i].ps[j]<<",";
		cout<<endl;
	}
	*/
	
	int n2; cin>>n2;
	map<string, string> v;
	cin.get();
	for(int i=0; i<n2; i++)
	{
		string s1, s2;
		cin>>s1>>s2;
		v[s2]=s1;
	}
	
	/*
	for(int i=0; i<n2; i++)
		cout<<v[i].type<<","<<v[i].name<<",\n";
	*/
	
	int n3; cin>>n3;
	cin.get();
	while(n3--)
	{
		getline(cin, s);
		functions t;
		int i=0;
		while(s[i++]==' ') ;	// 去除前面的空格
		s.erase(0, i-1);
		string name;
		for(i=0; i<s.find("("); i++)
			if(s[i]!=' ')
				name+=s[i];
		t.name=name;
		//cout<<name<<endl;
		i++;
		string psn;
		for(; i<s.size(); i++)
			if(s[i]!=' ' && s[i]!=',' && s[i]!=')')
				psn+=s[i]；
			else if(s[i]==',' || s[i]==')')
			{
				t.ps.push_back(v[psn]);
				psn.clear();
			}
		
		int cnt=0;
		for(int k=0; k<n1; k++)
			if(f[k]==t)
				cnt++;
		cout<<cnt<<endl;
	}

    return 0;
}

```


---


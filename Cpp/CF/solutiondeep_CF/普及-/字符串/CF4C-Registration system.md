# 题目信息

# Registration system

## 题目描述

### 题目背景

一个名为 "Berlanddesk" 的电子邮件系统即将在 Berland 上线运营。该电子邮件系统的管理员希望整个系统的建设可以尽早完成，因此他们找到了资深程序员您，希望您能够为他们开发一个用户注册系统的原型产品。

该系统的运行遵循以下原则:

新用户注册时，他将向系统发送一则内容为其用户名的请求，如果该用户名尚未存在于系统数据库内，则将该用户名插入数据库，同时用户得到回应信息 ```OK``` 表示其已经成功注册。如果用户请求的用户名已经存在于数据库内，那么系统将产生一个新的用户名并将其加入数据库。新用户名由用户请求的用户名与正整数 $i$ 构成，$i$ 为使 "用户名i" 尚未存在于数据库内的最小的 $i$。

## 样例 #1

### 输入

```
4
abacaba
acaba
abacaba
acab
```

### 输出

```
OK
OK
abacaba1
OK
```

## 样例 #2

### 输入

```
6
first
first
second
second
third
third
```

### 输出

```
OK
first1
OK
second1
OK
third1
```

# AI分析结果

【题目内容中文重写】
# 注册系统

## 题目描述

### 题目背景

一个名为 "Berlanddesk" 的电子邮件系统即将在 Berland 上线运营。该电子邮件系统的管理员希望整个系统的建设可以尽早完成，因此他们找到了资深程序员您，希望您能够为他们开发一个用户注册系统的原型产品。

该系统的运行遵循以下原则:

新用户注册时，他将向系统发送一则内容为其用户名的请求，如果该用户名尚未存在于系统数据库内，则将该用户名插入数据库，同时用户得到回应信息 ```OK``` 表示其已经成功注册。如果用户请求的用户名已经存在于数据库内，那么系统将产生一个新的用户名并将其加入数据库。新用户名由用户请求的用户名与正整数 $i$ 构成，$i$ 为使 "用户名i" 尚未存在于数据库内的最小的 $i$。

## 样例 #1

### 输入

```
4
abacaba
acaba
abacaba
acab
```

### 输出

```
OK
OK
abacaba1
OK
```

## 样例 #2

### 输入

```
6
first
first
second
second
third
third
```

### 输出

```
OK
first1
OK
second1
OK
third1
```

【题解分析与结论】
1. **题解思路对比**：
   - **SocietyNiu**：使用结构体存储用户名及其出现次数，通过遍历数组进行查找和更新。时间复杂度较高，适用于小规模数据。
   - **aiyougege**：利用`map`数据结构进行字符串到整数的映射，通过`find`函数判断字符串是否已存在，优化了查找效率。
   - **MujicaSaki**：使用两个`map`，一个存储用户名，另一个存储用户名后的数字，进一步优化了查找和更新操作。
   - **PC_DOS**：使用`map`存储用户名及其出现次数，通过直接访问`map`的值进行判断和更新，代码简洁且高效。

2. **最优思路**：
   - 使用`map`数据结构进行字符串到整数的映射，通过`find`函数判断字符串是否已存在，若存在则输出带数字的新用户名，否则输出"OK"并插入`map`。这种方法在时间和空间复杂度上均表现良好。

3. **关键技巧**：
   - 利用`map`的快速查找特性，避免线性查找带来的高时间复杂度。
   - 通过`map`的键值对存储，简化了数据的更新和查询操作。

4. **可拓展之处**：
   - 类似问题可以扩展到其他需要快速查找和更新的场景，如词频统计、唯一标识生成等。

【所选高星题解】
1. **aiyougege (5星)**
   - **关键亮点**：使用`map`进行字符串到整数的映射，通过`find`函数判断字符串是否已存在，代码简洁且高效。
   - **核心代码**：
     ```cpp
     map<string,int> m;
     int co[100005];//字符串出现几次
     int main(){
         int n;string str;
         scanf("%d",&n);
         map<string,int>::iterator it;//迭代器
         for(int i=1;i<=n;++i){
             cin>>str;it=m.find(str);//是否出现
             if(it==m.end()){m[str]=i;printf("OK\n");}
             else {
                 int s=it->second;//在数组co中位置
                 cout<<str<<++co[s]<<endl;
             }
         }
         return 0;
     }
     ```

2. **MujicaSaki (4星)**
   - **关键亮点**：使用两个`map`，一个存储用户名，另一个存储用户名后的数字，进一步优化了查找和更新操作。
   - **核心代码**：
     ```cpp
     map<string,int> m,m1;
     int main(){
         cin>>n;
         for(int i=1;i<=n;i++){
             cin>>s;
             if(m.find(s)==m.end()){
                 m[s]=i;
                 cout<<"OK"<<endl;
             }
             else{
                 cout<<s<<m1[s]+1<<endl;
                 m1[s]++;
             }
         }
     }
     ```

3. **PC_DOS (4星)**
   - **关键亮点**：使用`map`存储用户名及其出现次数，通过直接访问`map`的值进行判断和更新，代码简洁且高效。
   - **核心代码**：
     ```cpp
     map<string, long long> mapDatabase;
     int main(){
         ios::sync_with_stdio(false);
         string sNameInput;
         long long nCount,i;
         cin >> nCount;
         getline(cin, sNameInput);
         for (i = 1; i <= nCount; ++i){
             getline(cin, sNameInput);
             if (mapDatabase[sNameInput] != 0){
                 cout << sNameInput << mapDatabase[sNameInput] << '\n';
                 ++mapDatabase[sNameInput];
             }
             else{
                 cout << "OK\n";
                 mapDatabase[sNameInput] = 1;
             }
         }
         return 0;
     }
     ```

【推荐相似题目】
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)

---
处理用时：35.11秒
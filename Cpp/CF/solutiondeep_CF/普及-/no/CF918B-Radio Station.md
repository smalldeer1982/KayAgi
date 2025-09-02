# 题目信息

# Radio Station

## 题目描述

As the guys fried the radio station facilities, the school principal gave them tasks as a punishment. Dustin's task was to add comments to nginx configuration for school's website. The school has $ n $ servers. Each server has a name and an ip (names aren't necessarily unique, but ips are). Dustin knows the ip and name of each server. For simplicity, we'll assume that an nginx command is of form "command ip;" where command is a string consisting of English lowercase letter only, and ip is the ip of one of school servers.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF918B/ad878d2803e8a6ba1a8b3d8d599829e1c536a92a.png)Each ip is of form "a.b.c.d" where $ a $ , $ b $ , $ c $ and $ d $ are non-negative integers less than or equal to $ 255 $ (with no leading zeros). The nginx configuration file Dustin has to add comments to has $ m $ commands. Nobody ever memorizes the ips of servers, so to understand the configuration better, Dustin has to comment the name of server that the ip belongs to at the end of each line (after each command). More formally, if a line is "command ip;" Dustin has to replace it with "command ip; #name" where name is the name of the server with ip equal to ip.

Dustin doesn't know anything about nginx, so he panicked again and his friends asked you to do his task for him.

## 样例 #1

### 输入

```
2 2
main 192.168.0.2
replica 192.168.0.1
block 192.168.0.1;
proxy 192.168.0.2;
```

### 输出

```
block 192.168.0.1; #replica
proxy 192.168.0.2; #main
```

## 样例 #2

### 输入

```
3 5
google 8.8.8.8
codeforces 212.193.33.27
server 138.197.64.57
redirect 138.197.64.57;
block 8.8.8.8;
cf 212.193.33.27;
unblock 8.8.8.8;
check 138.197.64.57;
```

### 输出

```
redirect 138.197.64.57; #server
block 8.8.8.8; #google
cf 212.193.33.27; #codeforces
unblock 8.8.8.8; #google
check 138.197.64.57; #server
```

# AI分析结果

### 题目内容翻译
# 广播电台

## 题目描述
由于这些家伙弄坏了广播电台的设备，学校校长给他们布置了任务作为惩罚。达斯汀（Dustin）的任务是为学校网站的 nginx 配置添加注释。学校有 $n$ 台服务器。每台服务器都有一个名称和一个 IP 地址（名称不一定唯一，但 IP 地址是唯一的）。达斯汀知道每台服务器的 IP 地址和名称。为简单起见，我们假设 nginx 命令的形式为 “command ip;”，其中 command 是一个仅由英文字母小写组成的字符串，ip 是学校服务器之一的 IP 地址。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF918B/ad878d2803e8a6ba1a8b3d8d599829e1c536a92a.png)每个 IP 地址的形式为 “a.b.c.d”，其中 $a$、$b$、$c$ 和 $d$ 是非负整数，且小于或等于 255（没有前导零）。达斯汀需要添加注释的 nginx 配置文件中有 $m$ 条命令。没有人会记住服务器的 IP 地址，所以为了更好地理解配置，达斯汀必须在每行命令的末尾（每个命令之后）注释该 IP 地址所属服务器的名称。更正式地说，如果一行是 “command ip;”，达斯汀必须将其替换为 “command ip; #name”，其中 name 是 IP 地址等于 ip 的服务器的名称。

达斯汀对 nginx 一无所知，所以他又慌了，他的朋友们让你帮他完成这项任务。

## 样例 #1
### 输入
```
2 2
main 192.168.0.2
replica 192.168.0.1
block 192.168.0.1;
proxy 192.168.0.2;
```
### 输出
```
block 192.168.0.1; #replica
proxy 192.168.0.2; #main
```

## 样例 #2
### 输入
```
3 5
google 8.8.8.8
codeforces 212.193.33.27
server 138.197.64.57
redirect 138.197.64.57;
block 8.8.8.8;
cf 212.193.33.27;
unblock 8.8.8.8;
check 138.197.64.57;
```
### 输出
```
redirect 138.197.64.57; #server
block 8.8.8.8; #google
cf 212.193.33.27; #codeforces
unblock 8.8.8.8; #google
check 138.197.64.57; #server
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是先存储服务器的名称和 IP 地址的对应关系，然后对于每条命令中的 IP 地址，找到对应的服务器名称并按格式输出。不同题解的实现方式有所不同，主要区别在于数据结构的选择和 IP 地址的处理方式。

### 题解评分与分析
1. **风格雨关**：4星。关键亮点是使用 `map` 数据结构，利用其键值对的特性可以快速查找 IP 对应的名称，代码简洁，思路清晰。
2. **wangyilin**：3星。使用结构体存储 IP 地址的各个部分，通过遍历查找匹配的 IP 地址，思路较为常规，但代码相对复杂，查找效率较低。
3. **Eason_AC**：3星。同样是通过枚举查找匹配的 IP 地址，使用数组存储信息，代码中有自定义的输入输出函数，增加了代码的复杂度。
4. **zilingheimei**：2星。思路是在 IP 地址后添加分号再进行比较，但没有给出完整代码，实现细节不明确。
5. **applese**：3星。使用数组存储信息，通过遍历查找匹配的 IP 地址，在查找前删除 IP 地址后的分号，思路较为清晰，但查找效率较低。

### 所选高星题解
- **风格雨关（4星）**：关键亮点是使用 `map` 数据结构，能高效地根据 IP 地址查找对应的服务器名称。

### 重点代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
map<string,string> ip;
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        string a,b;
        cin>>b>>a;
        ip[a]=b;
    }
    for(int i=0;i<m;i++)
    {
        string b,a;
        cin>>b>>a;
        a=a.substr(0,a.size()-1); 
        cout<<b<<' '<<a<<"; #"<<ip[a]<<"\n";
    }
    return 0;
}
```
**核心实现思想**：使用 `map` 存储 IP 地址和服务器名称的对应关系，对于输入的命令，提取出 IP 地址（去除分号），然后通过 `map` 查找对应的服务器名称并按格式输出。

### 扩展思路
同类型题目通常会涉及字符串的处理和查找，例如查找文件路径对应的文件名、查找用户 ID 对应的用户名等。可以使用类似的思路，选择合适的数据结构（如 `map`、`unordered_map` 等）来存储对应关系，提高查找效率。

### 推荐题目
1. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
2. [P1200 [USACO1.1]你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)
3. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)

### 个人心得
风格雨关提到这道题看似高大上，但实际上很简单，果断选择用 `map` 来解决问题，体现了对数据结构的熟练运用可以简化问题的解决过程。 

---
处理用时：42.10秒
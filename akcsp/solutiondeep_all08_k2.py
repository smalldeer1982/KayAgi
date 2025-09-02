import os
import json
import requests
import time
from datetime import datetime

class AIProcessor:
    def __init__(self):
        # 读取配置文件
        config_path = os.path.join(os.path.dirname(__file__), 'config_k2.json')
        try:
            with open(config_path, 'r', encoding='utf-8') as f:
                config = json.load(f)
        except Exception as e:
            print(f"读取配置文件失败: {str(e)}")
            raise

        self.api_key = config.get('api_key')
        self.base_url = config.get('base_url')
        self.model = config.get('model')
        self.timeout = config.get('timeout', 1200)
        self.max_retries = config.get('max_retries', 3)
        self.retry_delay = config.get('retry_delay', 5)
        
        # 创建日志目录
        self.log_dir = os.path.join(os.path.dirname(__file__), 'logs')
        os.makedirs(self.log_dir, exist_ok=True)
        
        # 读取需求提示词
        prompt_path = os.path.join(os.path.dirname(__file__), 'prompt_C++题解分析提示词v8.md')
        try:
            with open(prompt_path, 'r', encoding='utf-8') as f:
                self.prompt_content = f.read().strip()
        except Exception as e:
            print(f"读取提示词文件失败: {str(e)}")
            self.prompt_content = "请分析上述题目和题解，总结关键思路和难点。"

    def preprocess_content(self, content):
        """预处理文件内容，规范化题解格式"""
        # 保存预处理前的内容到文件
        # with open('content_before.txt', 'w', encoding='utf-8') as f:
        #     f.write(content)
        
        # 找到第一个"# 题解"的位置
        first_solution = content.find("\n# 题解\n")
        if first_solution == -1:
            return content  # 没有题解，直接返回原内容
            
        # 分割成题目部分和第一个题解部分
        problem_part = content[:first_solution]
        solutions_part = content[first_solution:]
        
        # 将第一个"# 题解"后的其他"# 题解"替换为"## 作者"
        solutions_text = "\n# 题解\n"  # 保留第一个"# 题解"
        remaining_text = solutions_part[len("\n# 题解\n"):]  # 获取第一个"# 题解"之后的文本
        solutions_text += remaining_text.replace("\n# 题解\n", "\n")  # 替换剩余的所有"# 题解"
        
        # 重新组合内容
        processed_content = problem_part + solutions_text
        
        # 保存预处理后的内容到文件
        # with open('content_after.txt', 'w', encoding='utf-8') as f:
        #     f.write(processed_content)
        
        return processed_content

    def log_interaction(self, input_path, messages, response, error=None):
        """记录API交互日志"""
        timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
        log_file = os.path.join(self.log_dir, f'interaction_{timestamp}.json')
        
        log_data = {
            'timestamp': timestamp,
            'input_file': input_path,
            'request': {
                'model': self.model,
                'messages': messages
            },
            'response': response if not error else None,
            'error': str(error) if error else None
        }
        
        with open(log_file, 'w', encoding='utf-8') as f:
            json.dump(log_data, f, ensure_ascii=False, indent=2)
        
        print(f"交互日志已保存: {log_file}")

    def _call_llm_api(self, messages, filename_for_log):
        """调用大模型API

        Args:
            messages: 消息列表
            filename_for_log: 用于日志文件名的文件名

        Returns:
            dict: API响应结果
        """
        headers = {
            "Content-Type": "application/json",
            "Authorization": f"Bearer {self.api_key}"
        }

        data = {
            "model": self.model,
            "messages": messages,
            "temperature": 0.6,
            "max_tokens": 32768,
            "top_p": 0.95
        }

        try:
            api_url = f"{self.base_url}/chat/completions"
            
            response = requests.post(
                api_url,
                headers=headers,
                json=data,
                timeout=self.timeout
            )

            response.raise_for_status()
            result = response.json()
            
            return result

        except requests.exceptions.HTTPError as e:
            print(f"HTTP错误: {str(e)}")
            raise
        except Exception as e:
            print(f"API调用失败: {str(e)}")
            raise

    def process_content(self, content, input_path,prompt_type="c"):
        messages = None
        try:
            start_time = time.time()
            
            # 预处理内容
            content = self.preprocess_content(content)
            # 拆分题目内容和题解
            parts = content.split("\n# 题解\n")
            
            # 如果没有题解部分，就只处理题目部分
            if len(parts) == 1:
                problem_text = parts[0].strip()
                solutions_text = "# 题解\n\n暂无题解"  # 添加默认题解文本
            elif len(parts) == 2:
                problem_text = parts[0].strip()
                solutions_text = "# 题解\n" + parts[1].strip()
            else:
                raise ValueError("文件格式不正确，包含多个题解部分")
            
            
            if prompt_type == "cn":
                # 准备完整的待处理内容
                full_content = (
                    "【题目内容】\n"
                    f"{problem_text}\n\n"
                    "【题解信息】\n"
                    f"{solutions_text}"
                )
                
                # 准备带衔接语的内容
                formatted_content = f"\n\n待处理内容如下：\n\n{full_content}"
                
                # 替换占位符
                prompt_text = self.prompt_content
                if "{{content}}" in prompt_text:
                    user_prompt = prompt_text.replace("{{content}}", formatted_content)
                elif "{{CONTENT}}" in prompt_text:
                    user_prompt = prompt_text.replace("{{CONTENT}}", formatted_content)
                elif "{content}" in prompt_text:
                    user_prompt = prompt_text.replace("{content}", formatted_content)
                elif "[content]" in prompt_text:
                    user_prompt = prompt_text.replace("[content]", formatted_content)
                elif "<content>" in prompt_text:
                    user_prompt = prompt_text.replace("<content>", formatted_content)
                else:
                    # 如果没有找到任何已知占位符，则加上衔接语追加内容
                    user_prompt = prompt_text + "\n\n待处理内容如下：\n\n" + full_content
                
                # 构造消息
                messages = [
                    {
                        "role": "system",
                        "content": (
                            "你是一位专业的C++算法助理，帮助用户分析给定的C++题目及多条题解，需要对各题解进行要点提炼、难点对比，并给出精炼结论和可视化算法分析。人工智能助理，也是一位资深的双语内容分析专家，擅长提取文章精华、跨语言转化和数据可视化。你的分析需要准确、深入且富有洞察力。助理，也是一位资深的双语内容分析专家，擅长提取文章精华、跨语言转化和数据可视化。你的分析需要准确、深入且富有洞察力。"
                        )
                    },
                    {
                        "role": "user",
                        "content": user_prompt
                    }
                ]
            

            print(f"开始处理文件: {input_path}")
            print(f"消息长度: {len(str(messages))} 字符")
            print(f"正在调用 API...")
            
            try:
                # 调用API获取结果，包含重试逻辑
                completion = None
                retries = 0
                filename = os.path.basename(input_path)

                while retries < self.max_retries:
                    try:
                        completion = self._call_llm_api(messages, filename)
                        break
                    except Exception as e:
                        retries += 1
                        print(f"API调用失败 ({retries}/{self.max_retries}): {str(e)}")
                        if retries < self.max_retries:
                            retry_delay = self.retry_delay * retries  # 递增延迟
                            print(f"等待 {retry_delay} 秒后重试...")
                            time.sleep(retry_delay)
                        else:
                            print(f"达到最大重试次数，放弃处理文件 {input_path}")
                            raise
                
                print(f"API 调用成功，正在处理响应...")
                
                if not completion.get("choices"):
                    raise ValueError("API 响应中没有选项")
                
                response = {
                    'problem': problem_text,  # 添加题目内容
                    'answer': completion["choices"][0]["message"]["content"],
                    'processing_time': f"{time.time() - start_time:.2f}秒"
                }
                
                # 记录成功的交互
                self.log_interaction(input_path, messages, response)
                
                return response
                
            except Exception as api_error:
                error_msg = f"API 调用错误: {type(api_error).__name__}: {str(api_error)}"
                print(error_msg)
                # 记录详细错误信息到日志
                self.log_interaction(input_path, messages, None, error=error_msg)
                raise
            
        except Exception as e:
            error_msg = f"处理出错: {type(e).__name__}: {str(e)}"
            print(error_msg)
            # 记录详细错误信息到日志
            self.log_interaction(input_path, messages, None, error=error_msg)
            return None

    def process_file(self, input_path, output_path, prompt_type="c"):
        """
        处理单个文件
        Args:
            input_path: 输入文件路径
            output_path: 输出文件路径
            prompt_type: 提示词类型，"c" 用于中文题目，"f" 用于外文题目
        """
        try:
            # 确保输出目录存在
            os.makedirs(os.path.dirname(output_path), exist_ok=True)
            
            # 检查输入文件是否存在
            if not os.path.exists(input_path):
                raise FileNotFoundError(f"输入文件不存在: {input_path}")
            
            # 读取输入文件
            try:
                with open(input_path, 'r', encoding='utf-8') as f:
                    content = f.read()
            except Exception as e:
                raise IOError(f"读取输入文件失败: {str(e)}")
            
            # 处理内容，传入 prompt_type 参数
            result = self.process_content(content, input_path, prompt_type)
            if result:
                # 写入输出文件
                try:
                    with open(output_path, 'w', encoding='utf-8') as f:
                        # 写入题目信息
                        f.write("# 题目信息\n\n")
                        f.write(result['problem'])
                        f.write("\n\n")  # 添加空行分隔
                        
                        # 写入AI分析结果
                        f.write("# AI分析结果\n\n")
                        f.write(result['answer'])
                        
                        # 可选：写入处理时间
                        f.write(f"\n\n---\n处理用时：{result['processing_time']}")

                    print(f"已处理: {input_path} -> {output_path}")
                except Exception as e:
                    raise IOError(f"写入输出文件失败: {str(e)}")
            else:
                print(f"处理失败，未生成结果: {input_path}")
            
        except Exception as e:
            print(f"文件处理出错 {input_path}: {type(e).__name__}: {str(e)}")

def process_directory(input_dir, output_dir, prompt_type="c"):
    processor = AIProcessor()
    
    for root, dirs, files in os.walk(input_dir):
        # 计算相对路径
        rel_path = os.path.relpath(root, input_dir)
        
        for file in files:
            if file.endswith('.md'):
                # 构建输入和输出文件的完整路径
                input_path = os.path.join(root, file)
                output_path = os.path.join(output_dir, rel_path, f"{file}")
                
                # 处理文件
                processor.process_file(input_path, output_path, prompt_type)
                # 添加延迟以避免API限制
                time.sleep(1)

if __name__ == "__main__":
    # 设置输入和输出目录
    input_directory = "d:/ChatgptKay/KayAgi/Cpp/Luogu/solution/普及/动态规划"
    output_directory = "d:/ChatgptKay/KayAgi/Cpp/Luogu/solutiondeep_visualds3/普及/动态规划"
    
    prompt_type="cn"
    # 开始处理
    process_directory(input_directory, output_directory,prompt_type)
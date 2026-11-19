#include<iostream>
#include<string>
#include<vector>
#include<limits>
#include<algorithm>
 

struct Todo {
	int id = 0;
	std::string text;
	bool done = false;
};

class TodoManager {
private:
	std::vector<Todo>todos;
	int nextId = 1;

	void printAll()const {
		if (todos.empty()) {
			std::cout << "没有待办\n";
			return;
		}
		for (const Todo& t : todos) {
			std::cout << "#" << t.id
				<< "[" << (t.done ? "×" : " ") << "]"
				<< t.text << "\n";
		}
	}
	void addTodo() {
		std::cout << "请输入待办内容：";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::string input_text;
		std::getline(std::cin, input_text);

		if (input_text.empty()) {
			std::cout << "内容不能为空\n";
			return;
		}
		todos.push_back(Todo{ nextId,input_text,false });
		std::cout << "已添加 #" << nextId << "\n";
		nextId++;
	}
	bool markAsDone(int target_id) {
		for (Todo& t : todos) {
			if (target_id == t.id) {
				t.done = true;
				return true;
			}
		}
		return false;
	}
	void deleteTodo() {
		std::cout << "要删除的编号：";
		int target_id = 0;
		if (!(std::cin >> target_id)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "输入不为整数\n";
			return;
		}
		auto removed = std::erase_if(todos, 
			[target_id](const Todo& t) {return t.id == target_id; });
		if (removed > 0) {
			std::cout << "已删除 #" << target_id << "\n";
		}
		else {
			std::cout << "编号不存在\n";
		}
	}
	
public:
	void run() {
		int choice = 0;
		while (true) {
			std::cout << "\n=== 待办清单 ===\n";
			std::cout << "1. 添加  2. 列出  3. 完成  4. 删除  0. 退出\n> ";

			if (!(std::cin >> choice)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "请输入数字：";
				continue;
			}
			if (choice == 0) {
				break;
			}
			switch (choice) {
			case 1:
				addTodo();
				break;
			case 2:
				printAll();
				break;
			case 3: {
				int input_id = 0;
				std::cout << "完成的待办编号：";
				std::cin >> input_id;
				if (markAsDone(input_id)) {
					std::cout << "标记成功\n";
				}
				else {
					std::cout << "编号不存在\n";
				}
				break;
				}
			case 4:
				deleteTodo();
			    break;
			    default:
					std::cout << "无效选项\n";
				    break;
			}
		}
		std::cout << "bye\n";
	}

};

int main() {
	TodoManager app;
	app.run();
	std::cout << "程序结束\n";
	return 0;
}
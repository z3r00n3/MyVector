#pragma once

#include <vector>
#include <iostream>

namespace Tree
{
	template<typename UserType>
	struct Node
	{
		Node<UserType>*              parent_node_ptr;
		std::vector<Node<UserType>*> childs;
		const UserType*              key;
		std::size_t                  level;
		bool                         destruction;
		//std::size_t                  object_size_bytes;
	};

	template<typename UserType>
	class Tree
	{
	public:
		Tree();
		~Tree();

		Node<UserType>* add_node(UserType* parent_key, UserType* key);
		Node<UserType>* mark_as_destructed(const UserType* key);
		void print_tree() const;

	private:
		Node<UserType>* _search_node(const UserType* key, Node<UserType>* current_node_ptr) const;
		Node<UserType>* _root_node_ptr;

		void _print_tree(const Node<UserType>* current_node_ptr) const;
		void _destruct_nodes(Node<UserType> *current_node_ptr);
	};
	
	template<typename UserType>
	Tree<UserType>::Tree()
	{
		_root_node_ptr = new Node<UserType>();
	}

	template<typename UserType>
	Tree<UserType>::~Tree()
	{
		if (_root_node_ptr)
		{
			_destruct_nodes(_root_node_ptr);
		}
	}

	template<typename UserType>
	Node<UserType>* Tree<UserType>::add_node(UserType* parent_key, UserType* key)
	{
		Node<UserType>* new_node_ptr = new Node<UserType>();

		if (!parent_key)
		{
			new_node_ptr->parent_node_ptr = _root_node_ptr;
			new_node_ptr->key             = key;
			new_node_ptr->level           = new_node_ptr->parent_node_ptr->level + 1;

			_root_node_ptr->childs.push_back(new_node_ptr);
		}
		else
		{
			Node<UserType>* parent_node_ptr = _search_node(parent_key, _root_node_ptr);

			if (parent_node_ptr)
			{
				new_node_ptr->parent_node_ptr = parent_node_ptr;
				new_node_ptr->key             = key;
				new_node_ptr->level           = new_node_ptr->parent_node_ptr->level + 1;

				parent_node_ptr->childs.push_back(new_node_ptr);
			}
			else
			{
				return nullptr;
			}
		}

		return new_node_ptr;
	}

	template<typename UserType>
	Node<UserType>* Tree<UserType>::mark_as_destructed(const UserType* key)
	{
		Node<UserType>* current_node_ptr = _search_node(key, _root_node_ptr);

		if (current_node_ptr)
		{
			current_node_ptr->destruction = true;
		}

		return current_node_ptr;
	}

	template<typename UserType>
	void Tree<UserType>::print_tree() const
	{
		std::cout << "root" << std::endl;

		_print_tree(_root_node_ptr);
	}

	template<typename UserType>
	Node<UserType>* Tree<UserType>::_search_node(const UserType* key, Node<UserType>* current_node_ptr) const
	{
		Node<UserType>* found = nullptr;
		
		if (current_node_ptr)
		{
			if (current_node_ptr->key == key)
			{
				found = current_node_ptr;
			}
			else
			{
				for (std::size_t i = 0; i < current_node_ptr->childs.size(); i++)
				{
					found = _search_node(key, current_node_ptr->childs[i]);
					
					if (found)
					{
						break;
					}
				}
			}
		}

		return found;
	}
	
	template<typename UserType>
	void Tree<UserType>::_print_tree(const Node<UserType>* current_node_ptr) const
	{
		for (std::size_t i = 0; i < current_node_ptr->childs.size(); i++)
		{
			for (std::size_t j = 0; j < current_node_ptr->childs[i]->level; j++)
			{
				if (j == current_node_ptr->childs[i]->level - 1)
				{
					std::cout << "|----->";
				}
				std::cout << '\t';
			}

#ifdef _DEBUG
			std::cout << " node 0x" << current_node_ptr->childs[i] << ": key ";
#endif // _DEBUG

			std::cout << "0x" << current_node_ptr->childs[i]->key;

			if (current_node_ptr->childs[i]->destruction)
			{
				std::cout << " destructed";
			}
			std::cout << std::endl;

			_print_tree(current_node_ptr->childs[i]);
		}
	}

	template<typename UserType>
	void Tree<UserType>::_destruct_nodes(Node<UserType>* current_node_ptr)
	{
		for (std::size_t i = 0; i < current_node_ptr->childs.size(); i++)
		{
			_destruct_nodes(current_node_ptr->childs[i]);
		}

#ifdef _DEBUG
		std::cout << "destruction 0x" << current_node_ptr << std::endl;
#endif // _DEBUG

		delete current_node_ptr;
	}
}
#pragma once

#include <vector>
#include <iostream>

namespace Tree
{
	template<typename UserType>
	struct Node
	{
		Node<UserType>*              parent_ptr;
		std::vector<Node<UserType>*> childs;
		const UserType*              object_ptr;
		std::size_t                  level;
		//std::size_t                  object_size_bytes;
		//bool                         destruction;
	};

	template<typename UserType>
	class Tree
	{
	public:
		Tree();
		~Tree();

		Node<UserType>* add_node(const UserType* parent_object_ptr, const UserType* object_ptr);
		Node<UserType>* search_node(const UserType* object_ptr) const;
		void print_tree() const;
		//friend std::ostream& operator<<(std::ostream& out_stream, const Tree<UserType>& obj);
		Node<UserType>* _root_ptr;

	private:

		Node<UserType>* _search_node(const UserType* object_ptr, const Node<UserType>* current_node_ptr) const;
		void _print_tree(const Node<UserType>* current_node_ptr) const;
		void _destruct_nodes(Node<UserType> *current_node_ptr);
	};
	
	template<typename UserType>
	Tree<UserType>::Tree()
	{
		_root_ptr = new Node<UserType>();
	}

	template<typename UserType>
	Tree<UserType>::~Tree()
	{
		if (_root_ptr)
		{
			_destruct_nodes(_root_ptr);
		}
	}

	template<typename UserType>
	Node<UserType>* Tree<UserType>::add_node(const UserType* parent_object_ptr, const UserType* object_ptr)
	{
		Node<UserType>* new_node_ptr = new Node<UserType>();
		Node<UserType>* parent_ptr   = search_node(parent_object_ptr);
		
		if (parent_ptr)
		{
			new_node_ptr->parent_ptr = parent_ptr;
			new_node_ptr->object_ptr = object_ptr;
			new_node_ptr->level      = parent_ptr->level + 1;

			parent_ptr->childs.push_back(new_node_ptr);
		}
		else
		{
			new_node_ptr->parent_ptr = _root_ptr;
			new_node_ptr->object_ptr = object_ptr;
			new_node_ptr->level      = 1;

			_root_ptr->childs.push_back(new_node_ptr);
		}

		return new_node_ptr;
	}

	template<typename UserType>
	Node<UserType>* Tree<UserType>::search_node(const UserType* object_ptr) const
	{
		return _search_node(object_ptr, _root_ptr);
	}

	template<typename UserType>
	void Tree<UserType>::print_tree() const
	{
		_print_tree(_root_ptr);
	}

	template<typename UserType>
	Node<UserType>* Tree<UserType>::_search_node(const UserType* object_ptr, const Node<UserType>* current_node_ptr) const
	{
		if (object_ptr)
		{
			for (std::size_t i = 0; i < current_node_ptr->childs.size(); i++)
			{
				if (current_node_ptr->childs[i]->object_ptr == object_ptr)
				{
					std::cout << "i found parent 0x" << current_node_ptr->childs[i]->object_ptr << std::endl;
					std::cout << "his level = " << current_node_ptr->childs[i]->level << std::endl;
					return current_node_ptr->childs[i];
				}

				_search_node(object_ptr, current_node_ptr->childs[i]);
			}
		}

		return nullptr;
	}

	template<typename UserType>
	void Tree<UserType>::_print_tree(const Node<UserType>* current_node_ptr) const
	{
		for (std::size_t i = 0; i < current_node_ptr->childs.size(); i++)
		{
			std::cout << "0x" << current_node_ptr->childs[i]->object_ptr << std::endl;
			std::cout << "pl = " << current_node_ptr->level << " l = " << current_node_ptr->childs[i]->level << std::endl;

			_print_tree(current_node_ptr->childs[i]);
		}
	}

	template<typename UserType>
	void Tree<UserType>::_destruct_nodes(Node<UserType>* current_node_ptr)
	{
		for (std::size_t i = 0; i < current_node_ptr->childs.size(); i++)
		{
			_destruct_nodes(current_node_ptr->childs[i]);
			std::cout << "destruction 0x" << current_node_ptr << std::endl;
			delete current_node_ptr;
		}
	}
}
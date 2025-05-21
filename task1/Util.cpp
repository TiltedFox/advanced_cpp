#include "Util.h"
#include "User.h"
#include "Group.h"

#include <iostream>

bool Util::ContainsUser(unsigned int user_id) const
{
    for (auto iter = group_map_by_id_.begin(); iter != group_map_by_id_.end(); ++iter)
    {
        if (iter->second.ContainsUserById(user_id))
            return true;
    }

    return false;
}

bool Util::ContainsGroup(unsigned int group_id) const
{
    for (auto iter = group_map_by_id_.begin(); iter != group_map_by_id_.end(); ++iter)
    {
        if (iter->first == group_id)
            return true;
    }

    return false;
}

void Util::CreateUser(unsigned int id, std::string name)
{
    if (id == 0)
    {
        std::cerr << "User id must be greater than 0" << std::endl;
        return;
    }

    if (ContainsUser(id))
    {
        std::cerr << "User already exists" << std::endl;
        return;
    }

    std::shared_ptr<User> tmp = std::make_shared<User>(name, id);
    group_map_by_id_[0].AddUser(tmp);
}

void Util::DeleteUser(unsigned int id)
{
    if (!ContainsUser(id))
    {
        std::cerr << "User does not exist" << std::endl;
        return;
    }

    for (auto group_iter = group_map_by_id_.begin(); group_iter != group_map_by_id_.end(); ++group_iter)
    {
        if (group_iter->second.ContainsUserById(id))
        {
            std::cout << "deleting user, shared ptrs: " << group_iter->second.GetUserById(id).use_count() << std::endl;
            group_iter->second.RemoveUser(id);
            return;
        }
    }
}

void Util::AllUsers() const
{
    for (auto group_iter = group_map_by_id_.begin(); group_iter != group_map_by_id_.end(); ++group_iter)
        group_iter->second.AllUsers();
}

void Util::GetUser(unsigned int id)
{
    if (!ContainsUser(id))
    {
        std::cerr << "User does not exist" << std::endl;
        return;
    }

    for (auto group_iter = group_map_by_id_.begin(); group_iter != group_map_by_id_.end(); ++group_iter)
    {
        if (group_iter->second.ContainsUserById(id))
            std::cout << *group_iter->second.GetUserById(id) << std::endl;
    }
}

void Util::CreateGroup(unsigned int id)
{
    if (id == 0)
    {
        std::cerr << "Group number must be greater than 0" << std::endl;
        return;
    }

    if (ContainsGroup(id))
    {
        std::cerr << "Group already exists" << std::endl;
        return;
    }

    group_map_by_id_[id] = Group(id);
}

void Util::DeleteGroup(unsigned int id)
{
    if (id == 0)
    {
        std::cerr << "Group num should be more than 0!" << std::endl;
        return;
    }

    if (!ContainsGroup(id))
    {
        std::cerr << "Group does not exist" << std::endl;
        return;
    }

    group_map_by_id_[id].MoveUsersToOtherGroup(group_map_by_id_[0]);
    group_map_by_id_.erase(id);
}

void Util::AllGroups() const
{
    for (auto group_iter = group_map_by_id_.begin(); group_iter != group_map_by_id_.end(); ++group_iter)
        std::cout << group_iter->second << std::endl;
}

void Util::GetGroup(unsigned int id)
{
    if (!ContainsGroup(id))
    {
        std::cerr << "Group does not exist" << std::endl;
        return;
    }

    std::cout << group_map_by_id_[id] << std::endl;
}

void Util::AttachUserToGroup(unsigned int user_id, unsigned int group_id)
{
    if (!ContainsUser(user_id))
    {
        std::cerr << "User does not exist" << std::endl;
        return;
    }

    if (!ContainsGroup(group_id))
    {
        std::cerr << "Group does not exist" << std::endl;
        return;
    }

    // find user group
    unsigned int user_group_id = 0;
    for (auto group_iter = group_map_by_id_.begin(); group_iter != group_map_by_id_.end(); ++group_iter)
    {
        if (group_iter->second.ContainsUserById(user_id))
        {
            user_group_id = group_iter->first;
            break;
        }
    }

    if (group_id == user_group_id)
    {
        if (group_id == 0)
            std::cerr << "User has no group" << std::endl;
        else
            std::cerr << "Same group as User's" << std::endl;

        return;
    }

    group_map_by_id_[group_id].AddUser(group_map_by_id_[user_group_id].GetUserById(user_id));
    group_map_by_id_[user_group_id].RemoveUser(user_id);
}

void Util::DetachUserFromGroup(unsigned int user_id)
{
    AttachUserToGroup(user_id, 0);
}

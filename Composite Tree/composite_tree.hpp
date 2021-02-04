/*
    Tree application, represents a hierarchy of directories. 
    Using Composite design pattern.
    provides the following functions:
    -Create - loads a directory tree structure into memory.
    -Print - prints the tree into output stream.
    -Find - finds a file/directory in tree. 

    note: The user should provide the full path of the directory with / at the end.

    Ver:  0.1  API team - ready for review
    Ver:  0.2  Mentor approval.
    Ver:  0.3  Adding function as GetName
*/

#ifndef ILRD_HRD14_COMPOSITE_TREE_HPP
#define ILRD_HRD14_COMPOSITE_TREE_HPP

#include <vector>
#include <string>
#include <memory>


namespace hrd14
{
class File : public std::enable_shared_from_this<File>
{
public:
    explicit File(const std::string& name);
    virtual ~File() = default;
    
    File(const File& other) = delete;
    File& operator=(const File& other) = delete;
    virtual void Print(std::ostream& os, size_t level = 0, std::string tree_branch = "") const;
    
    const std::string GetName() const; 

    virtual std::shared_ptr<const File> Find(const std::string& name) const;
private:
    std::string m_name;
};

class Directory : public File
{
public:
    //If successful returns pointer to directory, otherwise returns nullptr.
    //Can throw bad_alloc exception.
    //If opendir fails, the function skips said directory.

    static std::shared_ptr<Directory> Create(const std::string& path);
    virtual ~Directory() = default;


    virtual void Print(std::ostream& os, size_t level = 0, std::string tree_branch = "") const override;
    
    //name argument can be file name or directory name.
    virtual std::shared_ptr<const File> Find(const std::string& name) const;
private:
    explicit Directory(const std::string& name);
    
    void Add(std::shared_ptr<File> file);
    std::vector<std::shared_ptr<File>> m_files;
};

} //namespace hrd14

#endif //ILRD_HRD14_COMPOSITE_TREE_HPP
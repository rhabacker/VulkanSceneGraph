/* <editor-fold desc="MIT License">

Copyright(c) 2018 Robert Osfield

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

</editor-fold> */

#include <vsg/nodes/MaskGroup.h>

#include <vsg/io/Input.h>
#include <vsg/io/Options.h>
#include <vsg/io/Output.h>

using namespace vsg;

MaskGroup::MaskGroup(Allocator* allocator) :
    Inherit(allocator)
{
}

MaskGroup::~MaskGroup()
{
}

void MaskGroup::read(Input& input)
{
    Node::read(input);

    children.resize(input.readValue<uint32_t>("NumChildren"));
    for (auto& child : children)
    {
        input.read("mask", child.mask);
        input.readObject("node", child.node);
    }
}

void MaskGroup::write(Output& output) const
{
    Node::write(output);

    output.writeValue<uint32_t>("NumChildren", children.size());
    for (auto& child : children)
    {
        output.write("mask", child.mask);
        output.writeObject("node", child.node);
    }
}

void MaskGroup::addChild(uint32_t mask, ref_ptr<Node> child)
{
    children.push_back(Child{mask, child});
}

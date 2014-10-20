#pragma once
struct ShaderSource_ShaderLocationDescription{
	int name, type;
};
struct ShaderSource_Shader_IDs{
	unsigned int vertex_id, fragment_id;

};
class Shader_Source{
private:
	unsigned int compileshader(const int& shader_type, const ShaderSource_ShaderLocationDescription& shader_info);
	ShaderSource_ShaderLocationDescription m_vertex, m_fragment;
	ShaderSource_Shader_IDs shader_ids = {};
public:
	Shader_Source(ShaderSource_ShaderLocationDescription vertex, ShaderSource_ShaderLocationDescription shader);
	ShaderSource_Shader_IDs setup_for_usage_by_program();



};
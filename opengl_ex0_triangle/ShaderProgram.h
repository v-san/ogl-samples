#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <unordered_map>
#include "common.h"


class ShaderProgram
{
public:

  ShaderProgram() : programObj(-1) {};

  ShaderProgram(const std::unordered_map<GLenum, std::string> &inputShaders);

  virtual ~ShaderProgram() {};

  void Release(); //actual destructor

  virtual void StartUseShader() const;

  virtual void StopUseShader() const;

  GLuint GetProgram() const { return programObj; }


  bool reLink();

  void SetUniform(const std::string &location, float value) const;

  void SetUniform(const std::string &location, double value) const;

  void SetUniform(const std::string &location, int value) const;

  void SetUniform(const std::string &location, unsigned int value) const;

  GLuint programObj;

private:
  static GLuint LoadShaderObject(GLenum type, const std::string &filename);
  std::unordered_map<GLenum, GLuint> shaderObjects;
};


#endif
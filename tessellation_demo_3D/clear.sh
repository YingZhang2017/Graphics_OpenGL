#!/bin/bash
# clean exist compile files and executable program

echo "Cleaning..."
if [ -e gl_utils.gcda ]; then
  rm  gl_utils.gcda
fi

if [ -e gl_utils.gcno ]; then
  rm  gl_utils.gcno
fi

if [ -e Shader.gcda ]; then
  rm  Shader.gcda
fi

if [ -e Shader.gcno ]; then
  rm  Shader.gcno
fi

if [ -e main.gcda ]; then
  rm  main.gcda
fi

if [ -e main.gcno ]; then
  rm  main.gcno
fi

if [ -e Shape3D.gcda ]; then
  rm  Shape3D.gcda
fi

if [ -e Shape3D.gcno ]; then
  rm  Shape3D.gcno
fi

if [ -e Cube.gcda ]; then
  rm  Cube.gcda
fi

if [ -e Scene.gcno ]; then
  rm  Scene.gcno
fi

if [ -e Scene.gcda ]; then
  rm  Scene.gcda
fi

if [ -e Cube.gcno ]; then
  rm  Cube.gcno
fi


if [ -e tessellation_demo ]; then
  rm  tessellation_demo
fi

echo "Done"

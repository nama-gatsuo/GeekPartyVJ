'use strict';

var gulp = require('gulp');
var sourcemaps = require('gulp-sourcemaps');
var babel = require('gulp-babel');

gulp.task('server:watch', function(){
    gulp.watch('./src/server/*.js', ['server']);
});

gulp.task('server', function(){
    gulp.src('./src/server/*.js')
        .pipe(sourcemaps.init())
        .pipe(babel({ presets: ['es2015'] }))
        .pipe(sourcemaps.write('.'))
        .pipe(gulp.dest('./server'));
});

gulp.task('default', [ 'server:watch' ]);
